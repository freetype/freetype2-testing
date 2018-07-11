// glyphloaditerator-naive.cpp
//
//   Implementation of GlyphLoadIteratorNaive.
//
// Copyright 2018 by
// Armin Hasitzka, David Turner, Robert Wilhelm, and Werner Lemberg.
//
// This file is part of the FreeType project, and may only be used,
// modified, and distributed under the terms of the FreeType project
// license, LICENSE.TXT.  By continuing to use, modify, or distribute
// this file you indicate that you have read the license and
// understand and accept it fully.


#include "iterators/glyphloaditerator-naive.h"

#include "utils/logging.h"


  void
  GlyphLoadIteratorNaive::
  run( Unique_FT_Face  face )
  {
    FT_Error  error;
    
    FT_Long  num_glyphs = face->num_glyphs;

    FT_Glyph         glyph;
    FT_Glyph         glyph_fake;
    Unique_FT_Glyph  uglyph = make_unique_glyph();
    

    for ( auto  index = 0;
          index < num_glyphs &&
            index < GLYPH_INDEX_MAX;
          index++ )
    {
      LOG( INFO ) << "using glyph " << ( index + 1 ) << "/" << num_glyphs;

      error = FT_Load_Glyph( face.get(), index, load_flags );

      if ( error != 0 )
      {
        LOG( ERROR ) << "FT_Load_Glyph failed: " << error;
        continue; // try the next glyph; it might work better.
      }

      error = FT_Get_Glyph( face->glyph, &glyph );

      if ( error != 0 )
      {
        LOG( ERROR ) << "FT_Get_Glyph failed: " << error;
        continue; // try the next glyph; it might work better.
      }

      uglyph = make_unique_glyph( glyph );

      for ( auto&  visitor : glyph_visitors )
      {
        error = FT_Glyph_Copy( uglyph.get(), &glyph_fake );

        if ( error != 0 )
        {
          LOG( ERROR ) << "FT_Glyph_Copy failed: " << error;
          break; // we can expect this action to fail again; bail out!
        }
        
        visitor->run( make_unique_glyph( glyph_fake ) );
      }
    }

    WARN_ABOUT_IGNORED_VALUES( num_glyphs, GLYPH_INDEX_MAX, "glyphs" );
  }
