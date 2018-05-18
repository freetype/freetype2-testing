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

cmake_minimum_required(VERSION 3.0)

project(fuzzing)

set(FUZZ_TARGET_TYPE "$ENV{CMAKE_FUZZ_TARGET_TYPE}")

set(FREETYPE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/../freetype2")

set(FUZZING_CORPORA_DIR "${CMAKE_CURRENT_SOURCE_DIR}/corpora")
set(FUZZING_CORPORA_SUITES "legacy")

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

include_directories("${FREETYPE_SOURCE_DIR}/include")
link_directories("${FREETYPE_SOURCE_DIR}/objs/.libs")

enable_testing()

if("${FUZZ_TARGET_TYPE}" STREQUAL "driver")

  add_subdirectory(targets)
  add_subdirectory(driver)

  foreach(suite ${FUZZING_CORPORA_SUITES})
    set(suite_dir "${FUZZING_CORPORA_DIR}/${suite}")
    file(GLOB_RECURSE test_input_paths "${suite_dir}/*")
    foreach(test_input_path ${test_input_paths})
      string(REPLACE "${suite_dir}/" "" test_name "${test_input_path}")
      add_test(
        NAME "${suite}:${test_name}"
        COMMAND driver "--${suite}" "${test_input_path}")
    endforeach()
  endforeach()

elseif("${FUZZ_TARGET_TYPE}" STREQUAL "libfuzzer")

  # These flags cannot be set earlier since CMake defines a main function
  # itself when testing the compiler. Clang (obviously) fails when being
  # confronted with two main functions.

  set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fsanitize=fuzzer")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=fuzzer")
  set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -fsanitize=fuzzer")

  add_subdirectory(targets)
  add_subdirectory(libfuzzer)

endif()
