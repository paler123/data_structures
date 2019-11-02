data_structures_sources = [
  '../include/tree.cpp',
  '../include/trie.cpp'
]

data_structures_lib = library(
  'data_structures_lib',
  data_structures_sources,
  cpp_args : used_warnings,
  include_directories : data_structures_includes,
  install : true
)

data_structures_private_includes = include_directories('.')

data_structures_dep = declare_dependency(
  link_with : data_structures_lib,
  include_directories : data_structures_includes
)
