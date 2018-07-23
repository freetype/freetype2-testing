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


    virtual void
    run( const uint8_t*  data,
         size_t          size );


  private:


    vector<FT_UInt>  interpreter_versions{
      TT_INTERPRETER_VERSION_35,
      TT_INTERPRETER_VERSION_38,
      TT_INTERPRETER_VERSION_40
    };
  };


#endif // TARGETS_FONT_DRIVERS_TRUETYPE_RENDER_H_
