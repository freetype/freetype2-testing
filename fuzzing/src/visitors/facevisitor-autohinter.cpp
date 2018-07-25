// facevisitor-autohinter.cpp
//
//   Implementation of FaceVisitorAutohinter.
//
// Copyright 2018 by
// Armin Hasitzka.
//
// This file is part of the FreeType project, and may only be used,
// modified, and distributed under the terms of the FreeType project
// license, LICENSE.TXT.  By continuing to use, modify, or distribute
// this file you indicate that you have read the license and
// understand and accept it fully.


#include "visitors/facevisitor-autohinter.h"

#include <cassert>

#include <ft2build.h>
#include FT_MODULE_H 

#include "utils/logging.h"


  void
  FaceVisitorAutohinter::
  run( Unique_FT_Face  face )
  {
    FT_Error  error;


    assert( face != nullptr );

    for ( auto  warping : warpings )
    {
      LOG( INFO ) << "using warping: " << ( warping == 1 ? "yes" : "no" );

      (void) set_property( face, "warping", &warping );
      (void) load_glyphs( face );
    }

    (void) set_property( face, "warping", &default_warping );
  }


  void
  FaceVisitorAutohinter::
  set_property( Unique_FT_Face&  face,
                const string     property_name,
                const void*      value)
  {
    (void) FT_Property_Set( face->glyph->library,
                            "autofitter",
                            property_name.c_str(),
                            value );
  }


  void
  FaceVisitorAutohinter::
  load_glyphs( Unique_FT_Face&  face )
  {
    FT_Error  error;
    FT_Long   num_glyphs = face->num_glyphs;


    for ( auto  index = 0;
          index < num_glyphs &&
            index < GLYPH_INDEX_MAX;
          index++ )
    {
      LOG( INFO ) << "testing glyph " << ( index + 1 ) << "/" << num_glyphs;

      error = FT_Load_Glyph( face.get(), index, load_flags );

      LOG_IF( ERROR, error != 0 ) << "FT_Load_Glyph failed: " << error;
    }

    WARN_ABOUT_IGNORED_VALUES( num_glyphs, GLYPH_INDEX_MAX, "glyphs" );
  }
