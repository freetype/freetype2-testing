[![License: GPL
v2](https://img.shields.io/badge/License-GPL%20v2-blue.svg)](https://www.gnu.org/licenses/old-licenses/gpl-2.0.en.html)
[![Build Status](https://travis-ci.org/freetype/freetype2-testing.svg?branch=master)](https://travis-ci.org/freetype/freetype2-testing)

# FreeType

https://www.freetype.org

FreeType is a freely available software library to render fonts.

# Targets

Targets can be virtually of any shape or size.  They do not have to inherit
from a specific interface as long as they are capable of working with an input
blob of `const uint8_t*` whose length is measured in `size_t` (see
e.g. [`base.h`](/fuzzing/src/targets/base.h#L64)).  All targets get shipped in
a single static libray which is then linked by the
[driver](fuzzing/src/driver) and the [fuzzers](/fuzzing/src/fuzzers).  This
method results in a significant size overhead in the fuzz targets, however,
two main reasons lead to this decision:

1. Assembling the targets [in a single
   place](/fuzzing/src/targets/CMakeLists.txt) keeps the build process
   maintainable since there are many dependencies between the
   [targets](/fuzzing/src/targets), their [iterators](/fuzzing/src/iterators),
   and their [visitors](/fuzzing/src/visitors).

2. As of August 2018, [OSS-Fuzz](https://github.com/google/oss-fuzz) does not
   support any kind of dynamic linking.
