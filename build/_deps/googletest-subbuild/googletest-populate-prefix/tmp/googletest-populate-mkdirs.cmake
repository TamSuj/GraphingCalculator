# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

file(MAKE_DIRECTORY
  "/Users/tammy/Documents/GitHub/99_00_final_project-TamSuj/build/_deps/googletest-src"
  "/Users/tammy/Documents/GitHub/99_00_final_project-TamSuj/build/_deps/googletest-build"
  "/Users/tammy/Documents/GitHub/99_00_final_project-TamSuj/build/_deps/googletest-subbuild/googletest-populate-prefix"
  "/Users/tammy/Documents/GitHub/99_00_final_project-TamSuj/build/_deps/googletest-subbuild/googletest-populate-prefix/tmp"
  "/Users/tammy/Documents/GitHub/99_00_final_project-TamSuj/build/_deps/googletest-subbuild/googletest-populate-prefix/src/googletest-populate-stamp"
  "/Users/tammy/Documents/GitHub/99_00_final_project-TamSuj/build/_deps/googletest-subbuild/googletest-populate-prefix/src"
  "/Users/tammy/Documents/GitHub/99_00_final_project-TamSuj/build/_deps/googletest-subbuild/googletest-populate-prefix/src/googletest-populate-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "/Users/tammy/Documents/GitHub/99_00_final_project-TamSuj/build/_deps/googletest-subbuild/googletest-populate-prefix/src/googletest-populate-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "/Users/tammy/Documents/GitHub/99_00_final_project-TamSuj/build/_deps/googletest-subbuild/googletest-populate-prefix/src/googletest-populate-stamp${cfgdir}") # cfgdir has leading slash
endif()
