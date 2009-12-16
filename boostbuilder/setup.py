#!/usr/bin/python

"""
Distutils installer for jFlow
"""

try:
    # Load setuptools, to build a specific source package
    import setuptools
except ImportError:
    pass

import sys, os

import compiler

from distutils.core import setup
from distutils.command.install_data import install_data
from build_ext import build_ext, Extension
import utils





class main(object):
    
    def __init__(self, config, args):
        self.root     = os.curdir
        self.failed   = False
        self.config   = config
        self.args     = args
        self.builddir = getattr(config,'BUILD_DIR','build')
        self.sys      = utils.systeminfo()
        self.version  = getattr(config,'VERSION','0.01')
        v,dir         = utils.pythoninfo()
        self.pythonversion = v
        self.pythondir     = dir
        self.pythonlib     = 'python%s' % v.replace('.','')
        self.debug         = False
        if '-g' in args:
            self.debug = True
        self.setup()
        
    def __str__(self):
        return '%s installer' % self.name
        
    def Extension(self, *args, **kwargs):
        return Extension(*args, **kwargs)
    
    def pythoninclude(self):
        return os.path.join(self.pythondir,'include')
    
    def pythonlibdir(self):
        return os.path.join(self.pythondir,'libs')
        
    def getcpp(self, path):
        return utils.getExtensions(path, ('cpp','c'))
    
    def getPackages(self):
        return utils.getPackages(self.package.__path__[0])
    
    def boostdir(self):
        try:
            boost = self.config.BOOST_SOURCE
        except:
            raise ValueError("Boost source directory not specified")
        return boost 
    
    def numpydir(self):
        try:
            ny = self.config.NUMPY_INCLUDE
        except:
            raise ValueError("Numpy include directory not specified")
        return ny     
    
    def libdir(self, ext):
        return os.path.join('build','lib.win32-2.5\jflow\lib')
           
        
    def boost(self, lib = 'python', extralib = None):
        '''
        Create the a boost library extension object
        '''
        boost = self.boostdir()
        lib   = str(lib).lower()
        boostsrc = os.path.join(boost,'libs',lib,'src')
        boostlib = 'boost_%s' % lib
        define_macros = [('BOOST_ALL_NO_LIB',1),
                         ('BOOST_PYTHON_SOURCE',None)]
        #if not self.debug:
        #    define_macros.append(('NDEBUG',None))
            
        if os.path.isdir(boostsrc):
            sources = self.getcpp(boostsrc)
            return Extension(boostlib,
                             external_library = True,
                             source_directory = boostsrc,
                             language = 'c++',
                             sources = sources,
                             define_macros = define_macros,
                             libraries = extralib,
                             include_dirs = [boost])
        else:
            print "Cannot find %s package in %s." % (boostlib,boostsrc)
            self.failed = True
            return
        
    def setup(self):
        raise NotImplementedError
                
    def _setup(self, **setup_args):
        setup(cmdclass   = {'build_ext': build_ext},
              **setup_args)
    
