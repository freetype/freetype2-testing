// type1-render-tar.h
//
//   Fuzz target that renders Type 1 faces from tar archives.
//
// Copyright 2018 by
// Armin Hasitzka.
//
// This file is part of the FreeType project, and may only be used,
// modified, and distributed under the terms of the FreeType project
// license, LICENSE.TXT.  By continuing to use, modify, or distribute
// this file you indicate that you have read the license and
// understand and accept it fully.


#ifndef TARGETS_FONT_DRIVERS_TYPE_1_RENDER_TAR_H_
#define TARGETS_FONT_DRIVERS_TYPE_1_RENDER_TAR_H_


#include "targets/font-drivers/type1-render-base.h"


  class Type1RenderTarFuzzTarget
  : public Type1RenderFuzzTargetBase
  {
  public:


    Type1RenderTarFuzzTarget( void );
  };


#endif // TARGETS_FONT_DRIVERS_TYPE_1_RENDER_TAR_H_
