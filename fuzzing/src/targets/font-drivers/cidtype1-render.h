// cidtype1-render.h
//
//   Render CID Type 1 faces.
//
// Copyright 2018 by
// Armin Hasitzka.
//
// This file is part of the FreeType project, and may only be used,
// modified, and distributed under the terms of the FreeType project
// license, LICENSE.TXT.  By continuing to use, modify, or distribute
// this file you indicate that you have read the license and
// understand and accept it fully.


#ifndef TARGETS_FONT_DRIVERS_CID_TYPE_1_RENDER_H_
#define TARGETS_FONT_DRIVERS_CID_TYPE_1_RENDER_H_


#include "targets/base.h"


  class CidType1RenderFuzzTarget
  : public FuzzTarget
  {
  public:


    CidType1RenderFuzzTarget( void );


  private:


    static const FT_Long  NUM_USED_BITMAPS;
    static const FT_Long  NUM_USED_OUTLINES;
  };


#endif // TARGETS_FONT_DRIVERS_CID_TYPE_1_RENDER_H_
