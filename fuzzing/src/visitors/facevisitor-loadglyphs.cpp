// facevisitor-loadglyphs.cpp
//
//   Implementation of FaceVisitorLoadGlyphs.
//
// Copyright 2018 by
// Armin Hasitzka.
//
// This file is part of the FreeType project, and may only be used,
// modified, and distributed under the terms of the FreeType project
// license, LICENSE.TXT.  By continuing to use, modify, or distribute
// this file you indicate that you have read the license and
// understand and accept it fully.


#include "visitors/facevisitor-loadglyphs.h"

#include <set>
#include <vector>

#include "utils/logging.h"


  void
  FaceVisitorLoadGlyphs::
  run( Unique_FT_Face  face )
  {
    FT_Error  error;

    FT_Long  num_glyphs = face->num_glyphs;


    for ( auto  index = 0;
          index < num_glyphs &&
            index < GLYPH_INDEX_MAX;
          index++ )
    {
      LOG( INFO ) << "testing glyph " << ( index + 1 ) << "/" << num_glyphs;

      for ( auto  load_flags : this->load_flags )
      {
        LOG( INFO ) << "load flags: " << hex << load_flags;

        error = FT_Load_Glyph( face.get(), index, load_flags );

        if ( error != 0 )
        {
          LOG( ERROR ) << "FT_Load_Glyph failed: " << error;
          continue; // try the next flag; it might work better.
        }
      }
    }

    WARN_ABOUT_IGNORED_VALUES( num_glyphs, GLYPH_INDEX_MAX, "glyphs" );
  }


  void
  FaceVisitorLoadGlyphs::
  add_load_flags( FT_Int32  flags )
  {
    (void) load_flags.push_back( flags );
  }
