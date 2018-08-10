# CMakeLists.txt
#
# This script listens to a few environment variables:
#
#   CMAKE_DRIVER_EXE_NAME
#     (optional) Override the default name "driver".
#
#   CMAKE_FUZZING_ENGINE
#     If set:  set up everything to build the fuzzers.  The value is expected
#              to be a linkable library that contains the desired
#              implementation of the fuzzer.
#              For example: `-fsanitize=fuzzer'.
#     If not set:  set up everything to build the driver.
#
#   CMAKE_USE_LOGGER_GLOG
#     (optional) If set and `1', glog will be linked.
#
# Copyright 2018 by
# Armin Hasitzka.
#
# This file is part of the FreeType project, and may only be used, modified,
# and distributed under the terms of the FreeType project license,
# LICENSE.TXT.  By continuing to use, modify, or distribute this file you
# indicate that you have read the license and understand and accept it
# fully.

cmake_minimum_required(VERSION 3.0.2)

project(fuzzing)

# ----------------------------------------------------------------------------
# defines:

set(FUZZING_BASE_DIR    "${CMAKE_CURRENT_SOURCE_DIR}")
set(FUZZING_SRC_DIR     "${FUZZING_BASE_DIR}/src")
set(FUZZING_CORPORA_DIR "${FUZZING_BASE_DIR}/corpora")

# `FUZZ_TARGET_NAMES', `FUZZ_TARGET_CLASS_NAMES', and
# `FUZZ_TARGET_HEADER_PATHS' are filled by `add_fuzz_target()'.

set(FUZZ_TARGET_NAMES        "legacy")
set(FUZZ_TARGET_CLASS_NAMES  "x")
set(FUZZ_TARGET_HEADER_PATHS "x")

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")

set(SUBMODULES_DIR "${CMAKE_CURRENT_SOURCE_DIR}/../external")

set(FREETYPE_BASE_DIR       "${SUBMODULES_DIR}/freetype2")
set(FREETYPE_SRC_DIR        "${FREETYPE_BASE_DIR}/src")
set(FREETYPE_STATIC_LIBRARY "${FREETYPE_BASE_DIR}/objs/.libs/libfreetype.a")

set(GLOG_BASE_DIR       "${SUBMODULES_DIR}/glog")
set(GLOG_SRC_DIR        "${GLOG_BASE_DIR}/src")
set(GLOG_BUILD_DIR      "${GLOG_BASE_DIR}/build")
set(GLOG_STATIC_LIBRARY "${GLOG_BUILD_DIR}/libglog.a")

set(LIBARCHIVE_BASE_DIR       "${SUBMODULES_DIR}/libarchive")
set(LIBARCHIVE_SRC_DIR        "${LIBARCHIVE_BASE_DIR}/src")
set(LIBARCHIVE_STATIC_LIBRARY "${LIBARCHIVE_BASE_DIR}/.libs/libarchive.a")

# ----------------------------------------------------------------------------
# functions:

function(add_fuzz_target
    class_name
    header_path)

  string(REGEX MATCH "(^|/)([^/]+)\\.h$" out "${header_path}")

  if (NOT "${CMAKE_MATCH_COUNT}" EQUAL "2")
    message(FATAL_ERROR "invalid header path: '${header_path}'")
  endif()
  
  set(FUZZ_TARGET_NAMES
    ${FUZZ_TARGET_NAMES}
    "${CMAKE_MATCH_2}"
    PARENT_SCOPE)

  set(FUZZ_TARGET_CLASS_NAMES
    ${FUZZ_TARGET_CLASS_NAMES}
    "${class_name}"
    PARENT_SCOPE)

  set(FUZZ_TARGET_HEADER_PATHS
    ${FUZZ_TARGET_HEADER_PATHS}
    "${header_path}"
    PARENT_SCOPE)

endfunction()

# ----------------------------------------------------------------------------
# fuzz targets:

add_fuzz_target(
  "CffFuzzTarget"
  "targets/font-drivers/cff.h")
add_fuzz_target(
  "CffFtEngineFuzzTarget"
  "targets/font-drivers/cff-ftengine.h")
add_fuzz_target(
  "CffRenderFuzzTarget"
  "targets/font-drivers/cff-render.h")
add_fuzz_target(
  "CffRenderFtEngineFuzzTarget"
  "targets/font-drivers/cff-render-ftengine.h")

add_fuzz_target(
  "CidType1FuzzTarget"
  "targets/font-drivers/cidtype1.h")
add_fuzz_target(
  "CidType1FtEngineFuzzTarget"
  "targets/font-drivers/cidtype1-ftengine.h")
add_fuzz_target(
  "CidType1RenderFuzzTarget"
  "targets/font-drivers/cidtype1-render.h")
add_fuzz_target(
  "CidType1RenderFtEngineFuzzTarget"
  "targets/font-drivers/cidtype1-render-ftengine.h")

add_fuzz_target(
  "TrueTypeFuzzTarget"
  "targets/font-drivers/truetype.h")
add_fuzz_target(
  "TrueTypeRenderFuzzTarget"
  "targets/font-drivers/truetype-render.h")

add_fuzz_target(
  "Type1FuzzTarget"
  "targets/font-drivers/type1.h")
add_fuzz_target(
  "Type1FtEngineFuzzTarget"
  "targets/font-drivers/type1-ftengine.h")
add_fuzz_target(
  "Type1RenderFuzzTarget"
  "targets/font-drivers/type1-render.h")
add_fuzz_target(
  "Type1RenderFtEngineFuzzTarget"
  "targets/font-drivers/type1-render-ftengine.h")
add_fuzz_target(
  "Type1RenderTarFuzzTarget"
  "targets/font-drivers/type1-render-tar.h")
add_fuzz_target(
  "Type1TarFuzzTarget"
  "targets/font-drivers/type1-tar.h")

add_fuzz_target(
  "Type42FuzzTarget"
  "targets/font-drivers/type42.h")
add_fuzz_target(
  "Type42RenderFuzzTarget"
  "targets/font-drivers/type42-render.h")

add_fuzz_target(
  "WindowsFntFuzzTarget"
  "targets/font-drivers/windowsfnt.h")
add_fuzz_target(
  "WindowsFntRenderFuzzTarget"
  "targets/font-drivers/windowsfnt-render.h")

add_fuzz_target(
  "GlyphsOutlinesFuzzTarget"
  "targets/glyphs/outlines.h")

# ----------------------------------------------------------------------------
# environment options:

set(FUZZING_ENGINE "$ENV{CMAKE_FUZZING_ENGINE}")

set(DRIVER_EXE_NAME "driver")
if(NOT "$ENV{CMAKE_DRIVER_EXE_NAME}" STREQUAL "")
  set(DRIVER_EXE_NAME "$ENV{CMAKE_DRIVER_EXE_NAME}")
endif()

if("$ENV{CMAKE_USE_LOGGER_GLOG}")
  set(LOGGER_NAME "LOGGER_GLOG")
endif()

# ----------------------------------------------------------------------------
# build logic:

include_directories(
  "${FREETYPE_BASE_DIR}/include"
  "${FUZZING_SRC_DIR}"
  "${LIBARCHIVE_BASE_DIR}/libarchive")

if("${LOGGER_NAME}" STREQUAL "LOGGER_GLOG")
  include_directories(
    "${GLOG_BUILD_DIR}"
    "${GLOG_SRC_DIR}")
endif()

enable_testing()

add_subdirectory("${FUZZING_SRC_DIR}")
