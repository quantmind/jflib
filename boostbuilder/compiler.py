

from distutils.ccompiler import *
from distutils.sysconfig import customize_compiler
from utils import replace_method


def saferemove(cso,value):
    try:
        cso.remove(value)
    except (AttributeError, ValueError):
        pass
    
def safereplace(cso,values,rvalue):
    for value in values:
        saferemove(cso,value)
    if rvalue not in cso:
        cso.append(rvalue)


def CCompiler_customize(self, dist, debug = False, need_cxx=0):
    # See FCompiler.customize for suggested usage.
    log.info('customize %s' % (self.__class__.__name__))
    customize_compiler(self)
    if need_cxx:
        # In general, distutils uses -Wstrict-prototypes, but this option is
        # not valid for C++ code, only for C.  Remove it if it's there to
        # avoid a spurious warning on every compilation.  All the default
        # options used by distutils can be extracted with:

        # from distutils import sysconfig
        # sysconfig.get_config_vars('CC', 'CXX', 'OPT', 'BASECFLAGS',
        # 'CCSHARED', 'LDSHARED', 'SO')
        saferemove(self.compiler_so,'-Wstrict-prototypes')
        
        if debug:
            saferemove(self.compiler_so,'-DNDEBUG')
            safereplace(self.compiler_so,['-O','-O1','-O2','-O3'],'-O0')
        else:
            saferemove(self.compiler_so,'-g')
            safereplace(self.compiler_so,['-O','-O0','-O1','-O2'],'-O3')

        if hasattr(self,'compiler') and 'cc' in self.compiler[0]:
            if not self.compiler_cxx:
                if self.compiler[0].startswith('gcc'):
                    a, b = 'gcc', 'g++'
                else:
                    a, b = 'cc', 'c++'
                self.compiler_cxx = [self.compiler[0].replace(a,b)]\
                                    + self.compiler[1:]
        else:
            if hasattr(self,'compiler'):
                log.warn("#### %s #######" % (self.compiler,))
            log.warn('Missing compiler_cxx fix for '+self.__class__.__name__)
    return

replace_method(CCompiler, 'customize', CCompiler_customize)

