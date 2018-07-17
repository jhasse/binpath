project('binpath', ['c', 'cpp'], version : '1.0.0', license: 'zlib')

inc = include_directories('src')
src = ['src/binpath.cpp']
if target_machine.system() == 'linux'
	src += [
		'src/linux/binreloc.c',
	]
endif

lib = static_library('binpath', src)

binpath_dep = declare_dependency(include_directories : inc, link_with : lib)
