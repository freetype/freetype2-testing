// type1-render-base.h
//
//   Base class for fuzz targets that render Type 1 faces.
//
// Copyright 2018 by
// Armin Hasitzka.
//
// This file is part of the FreeType project, and may only be used,
// modified, and distributed under the terms of the FreeType project
// license, LICENSE.TXT.  By continuing to use, modify, or distribute
// this file you indicate that you have read the license and
// understand and accept it fully.


#ifndef TARGETS_FONT_DRIVERS_TYPE_1_RENDER_BASE_H_
#define TARGETS_FONT_DRIVERS_TYPE_1_RENDER_BASE_H_


#include "targets/base.h"


  class Type1RenderFuzzTargetBase
  : public FuzzTarget
  {
  public:


    Type1RenderFuzzTargetBase( void );
  };


#endif // TARGETS_FONT_DRIVERS_TYPE_1_RENDER_BASE_H_
