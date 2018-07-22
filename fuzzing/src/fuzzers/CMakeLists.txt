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
  cff-render
  cidtype1
  cidtype1-render
  truetype
  truetype-render
  type1
  type1-render

  glyphs-outlines)

# OSS-Fuzz does not allow shared objects.  Thus we have to link the fuzz
# targets as statically as possible.  Since this only affects builds on
# OSS-Fuzz's machines at the moment, we test for specific paths of static
# libraries of that environment and fall back to dynamic linking if all else
# fails.

set("link_libarchive" "archive")

set("oss_path_libarchive" "/usr/lib/x86_64-linux-gnu/libarchive.a")

if (EXISTS "${oss_path_libarchive}")
  set("link_libarchive" "${oss_path_libarchive}")
endif()

add_executable(libfuzzer-legacy
  "${FUZZING_SRC_DIR}/legacy/ftfuzzer.cc")

foreach(exe ${libfuzzer_exes})
  
  if(NOT "${exe}" STREQUAL "legacy")
    
    add_executable("libfuzzer-${exe}" "${exe}.cpp")

    target_link_libraries("libfuzzer-${exe}"
      PRIVATE
      fuzztargets)

  endif()

  target_link_libraries("libfuzzer-${exe}"
    PRIVATE
    "${link_libarchive}"
    "${FREETYPE_STATIC_LIBRARY}")

  # `-fsanitize=fuzzer' or `-lFuzzingEngine' cannot be set earlier since CMake
  # defines a main function when testing the compiler.  Clang (obviously)
  # fails when being confronted with two main functions.

  set_target_properties("libfuzzer-${exe}"
    PROPERTIES
    OUTPUT_NAME "${exe}"
    LINK_FLAGS  "${FUZZING_ENGINE}")

endforeach()
