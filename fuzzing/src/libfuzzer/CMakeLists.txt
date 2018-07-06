# CMakeLists.txt
#
# Copyright 2018 by
# Armin Hasitzka.
#
# This file is part of the FreeType project, and may only be used, modified,
# and distributed under the terms of the FreeType project license,
# LICENSE.TXT.  By continuing to use, modify, or distribute this file you
# indicate that you have read the license and understand and accept it
# fully.

set(libfuzzer_exes
  legacy
  cff
  cidtype1
  truetype
  type1)

add_executable(libfuzzer-legacy
  "${FREETYPE_SRC_DIR}/tools/ftfuzzer/ftfuzzer.cc")

foreach(exe ${libfuzzer_exes})
  
  if(NOT "${exe}" STREQUAL "legacy")
    add_executable("libfuzzer-${exe}" "${exe}.cpp")
    target_link_libraries("libfuzzer-${exe}"
      PRIVATE
      archive
      fontdriver-targets
      freetype
      glog)
  else()
    target_link_libraries("libfuzzer-${exe}"
      PRIVATE
      archive
      freetype)
  endif()

  # "-fsanitize=fuzzer" cannot be set earlier since CMake defines a main
  # function itself when testing the compiler.  Clang (obviously) fails when
  # being confronted with two main functions.

  target_compile_options("libfuzzer-${exe}"
    PRIVATE "-fsanitize=fuzzer-no-link")
  
  set_target_properties("libfuzzer-${exe}"
    PROPERTIES
    OUTPUT_NAME "${exe}"
    LINK_FLAGS  "-fsanitize=fuzzer")

endforeach()
