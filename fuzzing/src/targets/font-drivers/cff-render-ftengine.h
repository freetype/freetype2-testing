// cff-render-ftengine.h
//
//   Render CFF fonts using FreeType's hinting engine.
//
// Copyright 2019 by
// Armin Hasitzka.
//
// This file is part of the FreeType project, and may only be used,
// modified, and distributed under the terms of the FreeType project
// license, LICENSE.TXT.  By continuing to use, modify, or distribute
// this file you indicate that you have read the license and
// understand and accept it fully.


#ifndef TARGETS_FONT_DRIVERS_CFF_RENDER_FT_ENGINE_H_
#define TARGETS_FONT_DRIVERS_CFF_RENDER_FT_ENGINE_H_


#include "targets/font-drivers/cff-render.h"


  class CffRenderFtEngineFuzzTarget
    : public CffRenderFuzzTarget
  {
  public:


    CffRenderFtEngineFuzzTarget( void );
  };


#endif // TARGETS_FONT_DRIVERS_CFF_RENDER_FT_ENGINE_H_
