project('binpath', 'cpp', version : '1.0.0', license: 'zlib')

inc = include_directories('src')
lib = static_library('binpath', 'src/binpath.cpp')

binpath_dep = declare_dependency(include_directories : inc, link_with : lib)
