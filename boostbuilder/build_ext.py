import os
import sys 
from types import *
from distutils.errors import *
from distutils.dep_util import newer_group
from distutils.core import Extension as old_Extension
from distutils.command.build_ext import build_ext as _build_ext
from distutils import log

from utils import fullsplit


class external_object_filenames_hack(object):

    def __init__(self, builder, ext):
        self.builder  = builder
        self.compiler = builder.compiler
        self.ext      = ext
        
    def __call__(self,
                 source_filenames,
                 strip_dir=0,
                 output_dir=''):
        if output_dir is None:
            output_dir = ''
        obj_names = []
        sd = fullsplit(self.ext.source_directory)
        NB = len(sd)
        for src_name in source_filenames:
            # use normcase to make sure '.rc' is really '.rc' and not '.RC'
            (base, ext) = os.path.splitext (os.path.normcase(src_name))
            base = tuple(fullsplit(base)[NB:])
            base = os.path.join(self.ext.name,*base)
            if ext not in (self.compiler.src_extensions + ['.rc','.res']):
                raise UnknownFileError, \
                        "unknown file type '%s' (from '%s')" % \
                        (ext, src_name)
            if strip_dir:
                base = os.path.basename (base)
            if ext == '.res' or ext == '.rc':
                # these need to be compiled to object files
                obj_names.append (os.path.join (output_dir,
                                                base + ext + self.compiler.obj_extension))
            else:
                obj_names.append (os.path.join (output_dir,
                                                base + self.compiler.obj_extension))
        return obj_names


class Extension(old_Extension):
    
    def __init__ (self, *args, **kwargs):
        self.external_library = kwargs.pop('external_library',False)
        self.source_directory = kwargs.pop('source_directory',False)
        self.depends_on       = kwargs.pop('depends_on',[])
        old_Extension.__init__(self, *args, **kwargs)
        
        


class build_ext(_build_ext):
    """
    Specialized extension source builder for boost libraries
    """
    def build_extension(self, ext):
        if ext.depends_on:
            if self.package:
                pd  = self.package.split('.')
                dir = os.path.join(self.build_lib,*pd)
            else:
                dir = self.build_lib
            if dir not in ext.library_dirs:
                ext.library_dirs.append(dir)
                
        if ext.external_library:
            objf = self.compiler.object_filenames
            self.compiler.object_filenames = external_object_filenames_hack(self,ext)
            self.external_library = True
            _build_ext.build_extension(self, ext)
            self.compiler.object_filenames = objf
        else:
            self.external_library = False
            _build_ext.build_extension(self, ext)
            
    def get_export_symbols(self, ext):
        if ext.external_library:
            return None
        else:
            return _build_ext.get_export_symbols(self, ext)
        
    def get_ext_filename(self, ext_name):
        from distutils.sysconfig import get_config_var
        
        ext_path  = ext_name.split('.')
        if os.name == "os2":
            ext_path[len(ext_path) - 1] = ext_path[len(ext_path) - 1][:8]
        so_ext = get_config_var('SO')
        prefix = ''
        debug  = ''
        if self.debug:
            debug = '_debug'
            
        if self.external_library:
            if os.name == 'nt':
                so_ext = '.dll'
            elif os.name == 'posix':
                prefix = 'lib'
        
        ext_path[-1] = prefix + ext_path[-1] + debug
        return apply(os.path.join, ext_path) + so_ext
    
        
    def run (self):

        from distutils.ccompiler import new_compiler

        # 'self.extensions', as supplied by setup.py, is a list of
        # Extension instances.  See the documentation for Extension (in
        # distutils.extension) for details.
        #
        # For backwards compatibility with Distutils 0.8.2 and earlier, we
        # also allow the 'extensions' list to be a list of tuples:
        #    (ext_name, build_info)
        # where build_info is a dictionary containing everything that
        # Extension instances do except the name, with a few things being
        # differently named.  We convert these 2-tuples to Extension
        # instances as needed.

        if not self.extensions:
            return

        # If we were asked to build any C/C++ libraries, make sure that the
        # directory where we put them is in the library search path for
        # linking extensions.
        if self.distribution.has_c_libraries():
            build_clib = self.get_finalized_command('build_clib')
            self.libraries.extend(build_clib.get_library_names() or [])
            self.library_dirs.append(build_clib.build_clib)

        # Setup the CCompiler object that we'll use to do all the
        # compiling and linking
        self.compiler = new_compiler(compiler=self.compiler,
                                     verbose=self.verbose,
                                     dry_run=self.dry_run,
                                     force=self.force)
        hascpp = False
        for ext in self.extensions:
            l = ext.language or self.compiler.detect_language(ext.sources)
            if l == 'c++':
                hascpp = True
                break
        
        self.compiler.customize(self.distribution, self.debug, hascpp)
        # If we are cross-compiling, init the compiler now (if we are not
        # cross-compiling, init would not hurt, but people may rely on
        # late initialization of compiler even if they shouldn't...)
        
        #if os.name == 'nt' and self.plat_name != get_platform():
        #    self.compiler.initialize(self.plat_name)

        # And make sure that any compile/link-related options (which might
        # come from the command-line or from the setup script) are set in
        # that CCompiler object -- that way, they automatically apply to
        # all compiling and linking done here.
        if self.include_dirs is not None:
            self.compiler.set_include_dirs(self.include_dirs)
        if self.define is not None:
            # 'define' option is a list of (name,value) tuples
            for (name,value) in self.define:
                self.compiler.define_macro(name, value)
        if self.undef is not None:
            for macro in self.undef:
                self.compiler.undefine_macro(macro)
        if self.libraries is not None:
            self.compiler.set_libraries(self.libraries)
        if self.library_dirs is not None:
            self.compiler.set_library_dirs(self.library_dirs)
        if self.rpath is not None:
            self.compiler.set_runtime_library_dirs(self.rpath)
        if self.link_objects is not None:
            self.compiler.set_link_objects(self.link_objects)

        # Now actually compile and link everything.
        self.build_extensions()