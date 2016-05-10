#!/usr/bin/env python

import platform

def options(opt):
	opt.load('compiler_c compiler_cxx')

def configure(conf):
	conf.load('compiler_c compiler_cxx')

def build(bld):
	source_files = bld.path.ant_glob('src/*.cpp')
	if platform.system() == "Linux":
		bld.objects(source='src/linux/binreloc.c', target='binreloc', features='c',
		            defines='ENABLE_BINRELOC')
	bld.stlib(features='cxx', source=source_files,
	          target='binpath',
			  cxxflags=['-std=c++11'],
			  use='binreloc')
