// truetype-render.h
//
//   Fuzz target for rendering TrueType faces.
//
// Copyright 2018 by
// Armin Hasitzka.
//
// This file is part of the FreeType project, and may only be used,
// modified, and distributed under the terms of the FreeType project
// license, LICENSE.TXT.  By continuing to use, modify, or distribute
// this file you indicate that you have read the license and
// understand and accept it fully.


#ifndef TARGETS_FONT_DRIVERS_TRUETYPE_RENDER_H_
#define TARGETS_FONT_DRIVERS_TRUETYPE_RENDER_H_


#include <ft2build.h>
#include FT_DRIVER_H

#include "targets/base.h"


  class TrueTypeRenderFuzzTarget
  : public FuzzTarget
  {
  public:


    TrueTypeRenderFuzzTarget( void );


  protected:

    
    static const FT_UInt  INTERPRETER_VERSION_35;
    static const FT_UInt  INTERPRETER_VERSION_38;
    static const FT_UInt  INTERPRETER_VERSION_40;


  private:


    static const FT_Long  NUM_USED_BITMAPS;
    static const FT_Long  NUM_USED_OUTLINES;
  };


#endif // TARGETS_FONT_DRIVERS_TRUETYPE_RENDER_H_
