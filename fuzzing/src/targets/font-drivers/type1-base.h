// type1-base.h
//
//   Base class of fuzz target for Type 1 faces.
//
// Copyright 2018 by
// Armin Hasitzka.
//
// This file is part of the FreeType project, and may only be used,
// modified, and distributed under the terms of the FreeType project
// license, LICENSE.TXT.  By continuing to use, modify, or distribute
// this file you indicate that you have read the license and
// understand and accept it fully.


#ifndef TARGETS_FONT_DRIVERS_TYPE_1_BASE_H_
#define TARGETS_FONT_DRIVERS_TYPE_1_BASE_H_


#include "targets/base.h"


  class Type1FuzzTargetBase
  : public FuzzTarget
  {
  public:


    Type1FuzzTargetBase( void );
  };


#endif // TARGETS_FONT_DRIVERS_TYPE_1_BASE_H_
