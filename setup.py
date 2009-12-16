import sys
import os

import config
from boostbuilder import main


class jmain(main):
    
    def __init__(self, args):
        super(jmain,self).__init__(config, args)
        
    def setup(self):
        boost = self.boostdir()
        boost_python  = self.boost('python')
        if boost_python == None:
            print 'Could not find boost libraries'
            return
        bplib = boost_python.name
        if self.debug:
            bplib = '%s_debug' % bplib
            
        jflow_extenstions = self.Extension("_jflib",
                                           sources = self.getcpp("src"),
                                           include_dirs = ['include', boost,self.numpydir()],
                                           libraries    = [bplib,'lapack'],
                                           define_macros = [('BOOST_ALL_NO_LIB',1),
                                                            ('SCL_SECURE_NO_WARNINGS',1),
                                                            ('BOOST_UBLAS_CHECK_ENABLE',0),
                                                            ('__JFLIB_UBLAS_NUMPY_CONVERSION__',1)],
                                  depends_on   = boost_python)
    
        extension_libs = [boost_python,jflow_extenstions]
        pass
        self._setup(name             = "jflow",
                    version          = '0.1',
                    description      = "Quantitative financial library",
                    author           = "Dynamic Quant Limited",
                    author_email     = "luca@quantmind.com",
                    maintainer       = "Luca Sbardella",
                    maintainer_email = "luca@quantmind.com",
                    url              = "http://trac.quantmind.com/",
                    license          = "New BSD License",
                    long_description = """Quantitative financial library""",
                    #cmdclass         = {'install_data': install_data}, 
                    ext_package      = 'jflow.lib',
                    ext_modules      = extension_libs )


if __name__ == "__main__":
    jmain(sys.argv[1:])

