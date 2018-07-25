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
  "${FUZZING_SRC_DIR}/legacy/ftfuzzer.cc")

set_target_properties(driver PROPERTIES OUTPUT_NAME "${DRIVER_EXE_NAME}")

target_link_libraries(driver
  PRIVATE
  "${LIBARCHIVE_STATIC_LIBRARY}"
  fuzztargets
  "${FREETYPE_STATIC_LIBRARY}")

if("${LOGGER_NAME}" STREQUAL "LOGGER_GLOG")
  target_compile_definitions(driver PRIVATE "LOGGER_GLOG")
  target_link_libraries(     driver PRIVATE gflags glog)
endif()

foreach(suite ${FUZZING_CORPORA_SUITES})

  set(suite_dir "${FUZZING_CORPORA_DIR}/${suite}")
  file(GLOB_RECURSE test_input_paths "${suite_dir}/*")

  foreach(test_input_path ${test_input_paths})

    if("${test_input_path}" MATCHES "/README\\.md$")
      continue()
    endif()

    string(REPLACE "${suite_dir}/" "" test_name "${test_input_path}")
    set(full_test_name "${suite}:${test_name}")

    add_test(
      NAME "${full_test_name}"
      COMMAND driver "--${suite}" "${test_input_path}")

    set_tests_properties("${full_test_name}" PROPERTIES TIMEOUT 20)

  endforeach()

endforeach()
