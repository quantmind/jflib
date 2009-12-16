import os
import sys
import new
import platform


def fullsplit(path, result=None):
    """
    Split a pathname into components (the opposite of os.path.join) in a
    platform-neutral way.
    """
    if result is None:
        result = []
    head, tail = os.path.split(path)
    if head == '':
        return [tail] + result
    if head == path:
        return result
    return fullsplit(head, [tail] + result)



def replace_method(klass, method_name, func):
    '''
    Replace method 'method_name' in class 'klass' with function 'func'
    '''
    m = new.instancemethod(func, None, klass)
    setattr(klass, method_name, m)



def getPackages(root):
    # Compile the list of packages available, because distutils doesn't have
    # an easy way to do this.
    
    if os.path.isdir(root):
        
        packages, data_files = [], []
        
        for dirpath, dirnames, filenames in os.walk(root):
            
            # Ignore dirnames that start with '.'
            for i, dirname in enumerate(dirnames):
                if dirname.startswith('.'):
                    del dirnames[i]
            
            if '__init__.py' in filenames:
                packages.append('.'.join(fullsplit(dirpath)))
            elif filenames:
                data_files.append([dirpath, [os.path.join(dirpath, f) for f in filenames]])
        
        return packages, data_files
    
    else:
        raise ValueError
    
    
def getExtensions(dir, extens = None):
    """
    Get all extensions
    """
    if extens == None:
        extens = ('c','cc','cpp')
    extensions = []
    
    
    files = os.listdir(dir)
    for f in files:
        fullpath = os.path.join(dir,f)
        if os.path.isdir(fullpath):
            extensions.extend(getExtensions(fullpath,extens))
        else:
            sp = f.split('.')
            N  = len(sp)
            if N > 1 and sp[N-1] in extens:
                extensions.append(fullpath)                    
    return extensions


def pythoninfo():
    version     = sys.version[:3]
    installpath = sys.prefix
    return version,installpath



def libpaths(paths,bits):
    """Return a list of library paths valid on 32 or 64 bit systems.

    Inputs:
      paths : sequence
        A sequence of strings (typically paths)
      bits : int
        An integer, the only valid values are 32 or 64.  A ValueError exception
      is raised otherwise.

    Examples:

    Consider a list of directories
    >>> paths = ['/usr/X11R6/lib','/usr/X11/lib','/usr/lib']

    For a 32-bit platform, this is already valid:
    >>> libpaths(paths,32)
    ['/usr/X11R6/lib', '/usr/X11/lib', '/usr/lib']

    On 64 bits, we prepend the '64' postfix
    >>> libpaths(paths,64)
    ['/usr/X11R6/lib64', '/usr/X11R6/lib', '/usr/X11/lib64', '/usr/X11/lib',
    '/usr/lib64', '/usr/lib']
    """
    if bits not in (32, 64):
        raise ValueError("Invalid bit size in libpaths: 32 or 64 only")

    # Handle 32bit case
    if bits==32:
        return paths

    # Handle 64bit case
    out = []
    for p in paths:
        out.extend([p+'64', p])

    return out




class systeminfo(object):
    _bits = {'32bit':32,'64bit':64}
    
    def __init__(self):
        self.platform_bits = self._bits[platform.architecture()[0]]
        if sys.platform == 'win32':
            default_lib_dirs = []
            self.default_include_dirs = []
            self.default_src_dirs = ['.']
            self.default_x11_lib_dirs = []
            self.default_x11_include_dirs = []
        else:
            self.default_lib_dirs = libpaths(['/usr/local/lib','/opt/lib','/usr/lib',
                                 '/opt/local/lib','/sw/lib'], self.platform_bits)
            self.default_include_dirs = ['/usr/local/include',
                                    '/opt/include',
                                    '/usr/include',
                                    '/opt/local/include',
                                    '/sw/include',
                                    '/usr/include/suitesparse']
            self.default_src_dirs = ['.','/usr/local/src', '/opt/src','/sw/src']

            self.default_x11_lib_dirs = libpaths(['/usr/X11R6/lib','/usr/X11/lib',
                                     '/usr/lib'], self.platform_bits)
            self.default_x11_include_dirs = ['/usr/X11R6/include','/usr/X11/include',
                                        '/usr/include']



def svn_version():
    def _minimal_ext_cmd(cmd):
        # construct minimal environment
        env = {}
        path = os.environ.get('PATH')
        if path is not None:
            env['PATH'] = path
        # LANGUAGE is used on win32
        env['LANGUAGE'] = 'C'
        env['LANG'] = 'C'
        env['LC_ALL'] = 'C'
        out = subprocess.Popen(cmd, stdout = subprocess.PIPE, env=env).communicate()[0]
        return out

    try:
        out = _minimal_ext_cmd(['svn', 'info'])
    except OSError:
        print(" --- Could not run svn info --- ")
        return ""

    r = re.compile('Revision: ([0-9]+)')
    svnver = ""
    for line in out.split('\n'):
        m = r.match(line.strip())
        if m:
            svnver = m.group(1)

    if not svnver:
        print("Error while parsing svn version")

    return svnver

