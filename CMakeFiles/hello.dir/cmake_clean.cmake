FILE(REMOVE_RECURSE
  "CMakeFiles/hello.dir/main/main.o"
  "CMakeFiles/hello.dir/hello/hello.o"
  "hello.pdb"
  "hello"
)

# Per-language clean rules from dependency scanning.
FOREACH(lang CXX)
  INCLUDE(CMakeFiles/hello.dir/cmake_clean_${lang}.cmake OPTIONAL)
ENDFOREACH(lang)
