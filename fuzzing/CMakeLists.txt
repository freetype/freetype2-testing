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

# ${FUZZING_CORPORA_SUITES} is used to automatically detect and register
# regression tests.

set(FUZZING_CORPORA_SUITES
  "legacy"

  "cff"
  "cff-render"

  "cidtype1"
  "cidtype1-render"

  "truetype"
  "truetype-render"

  "type1"
  "type1-render"
  "type1-render-tar"
  "type1-tar"

  "windowsfnt"
  "windowsfnt-render")

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

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
# options:

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
