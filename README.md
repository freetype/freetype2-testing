[![License: GPL v2](https://img.shields.io/badge/License-GPL%20v2-blue.svg)](https://www.gnu.org/licenses/old-licenses/gpl-2.0.en.html)
[![Build Status](https://travis-ci.org/cherusker/freetype2-testing.svg?branch=master)](https://travis-ci.org/cherusker/freetype2-testing)

# FreeType

FreeType is a freely available software library to render fonts.

https://www.freetype.org/

# Testing

This repository provides testing utilities for FreeType.
Currently, we use [Travis CI](https://travis-ci.org/) to run nightly builds of [FreeType's master branch](http://git.savannah.gnu.org/cgit/freetype/freetype2.git/log/) to verify:

- **Fuzzing**: run FreeType against test cases that [OSS-Fuzz](https://bugs.chromium.org/p/oss-fuzz/issues/list?can=1&q=proj=freetype2) created to trigger verified bugs that have been fixed officially.
