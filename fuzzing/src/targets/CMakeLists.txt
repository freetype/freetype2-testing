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

add_library(fuzztargets
  STATIC
  "${FUZZING_SRC_DIR}/iterators/faceloaditerator.cpp"
  "${FUZZING_SRC_DIR}/iterators/faceprepiterator.cpp"
  "${FUZZING_SRC_DIR}/iterators/faceprepiterator-bitmaps.cpp"
  "${FUZZING_SRC_DIR}/iterators/faceprepiterator-multiplemasters.cpp"
  "${FUZZING_SRC_DIR}/iterators/faceprepiterator-outlines.cpp"
  "${FUZZING_SRC_DIR}/iterators/glyphloaditerator.cpp"
  "${FUZZING_SRC_DIR}/iterators/glyphloaditerator-naive.cpp"
  "${FUZZING_SRC_DIR}/iterators/glyphrenderiterator-allmodes.cpp"
  "${FUZZING_SRC_DIR}/targets/base.cpp"
  "${FUZZING_SRC_DIR}/targets/font-drivers/cff.cpp"
  "${FUZZING_SRC_DIR}/targets/font-drivers/cidtype1.cpp"
  "${FUZZING_SRC_DIR}/targets/font-drivers/truetype.cpp"
  "${FUZZING_SRC_DIR}/targets/font-drivers/type1.cpp"
  "${FUZZING_SRC_DIR}/targets/glyphs/outlines.cpp"
  "${FUZZING_SRC_DIR}/utils/faceloader.cpp"
  "${FUZZING_SRC_DIR}/utils/tarreader.cpp"
  "${FUZZING_SRC_DIR}/utils/utils.cpp"
  "${FUZZING_SRC_DIR}/visitors/facevisitor-cid.cpp"
  "${FUZZING_SRC_DIR}/visitors/facevisitor-charcodes.cpp"
  "${FUZZING_SRC_DIR}/visitors/facevisitor-kerning.cpp"
  "${FUZZING_SRC_DIR}/visitors/facevisitor-multiplemasters.cpp"
  "${FUZZING_SRC_DIR}/visitors/facevisitor-sfntnames.cpp"
  "${FUZZING_SRC_DIR}/visitors/facevisitor-truetypepatents.cpp"
  "${FUZZING_SRC_DIR}/visitors/facevisitor-truetypetables.cpp"
  "${FUZZING_SRC_DIR}/visitors/facevisitor-type1tables.cpp"
  "${FUZZING_SRC_DIR}/visitors/facevisitor-variants.cpp"
  "${FUZZING_SRC_DIR}/visitors/glyphvisitor-cbox.cpp"
  "${FUZZING_SRC_DIR}/visitors/glyphvisitor-transform.cpp")

target_compile_definitions(fuzztargets
  PRIVATE
  "${LOGGER_NAME}")

if("${FUZZ_TARGET_TYPE}" STREQUAL "libfuzzer")

  target_compile_options(fuzztargets
    PRIVATE "-fsanitize=fuzzer-no-link")

  set_target_properties(fuzztargets
    PROPERTIES LINK_FLAGS "-fsanitize=fuzzer-no-link")

endif()
