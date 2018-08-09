// type42.h
//
//   Fuzz target for Type 42 faces.
//
// Copyright 2018 by
// Armin Hasitzka.
//
// This file is part of the FreeType project, and may only be used,
// modified, and distributed under the terms of the FreeType project
// license, LICENSE.TXT.  By continuing to use, modify, or distribute
// this file you indicate that you have read the license and
// understand and accept it fully.


#ifndef TARGETS_FONT_DRIVERS_TYPE_42_H_
#define TARGETS_FONT_DRIVERS_TYPE_42_H_


#include "targets/base.h"


  class Type42FuzzTarget
  : public FuzzTarget
  {
  public:


    Type42FuzzTarget( void );
  };


#endif // TARGETS_FONT_DRIVERS_TYPE_42_H_
