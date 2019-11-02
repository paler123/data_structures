data_structures_ut_sources = [
  'tree.cpp',
  'trie.cpp',
  'tests.cpp'
]

data_structures_test_exe = executable(
    'data_structures_ut',
    data_structures_ut_sources,
    cpp_args : used_warnings,
    include_directories : data_structures_private_includes,
    dependencies : [data_structures_dep, catch2_dep]
)


test('data_structures_ut', data_structures_test_exe)
