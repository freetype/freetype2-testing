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

add_executable(driver
  "${FUZZING_SRC_DIR}/driver/driver.cpp"
  "${FREETYPE_SRC_DIR}/tools/ftfuzzer/ftfuzzer.cc")

target_compile_definitions(driver
  PRIVATE
  "${LOGGER_NAME}")

target_link_libraries(driver
  PRIVATE
  archive
  fontdriver-targets
  freetype
  gflags
  glog)

foreach(suite ${FUZZING_CORPORA_SUITES})

  set(suite_dir "${FUZZING_CORPORA_DIR}/${suite}")
  file(GLOB_RECURSE test_input_paths "${suite_dir}/*")

  foreach(test_input_path ${test_input_paths})

    string(REPLACE "${suite_dir}/" "" test_name "${test_input_path}")
    set(full_test_name "${suite}:${test_name}")

    add_test(
      NAME "${full_test_name}"
      COMMAND driver "--${suite}" "${test_input_path}")

    set_tests_properties("${full_test_name}" PROPERTIES TIMEOUT 20)

  endforeach()

endforeach()
