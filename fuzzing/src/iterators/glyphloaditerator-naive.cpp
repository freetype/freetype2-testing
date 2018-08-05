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

#include <cassert>

#include "utils/logging.h"


  void
  GlyphLoadIteratorNaive::
  run( Unique_FT_Face  face )
  {
    FT_Error  error;
    
    FT_Long  num_glyphs;

    FT_Glyph         raw_glyph;
    Unique_FT_Glyph  glyph = make_unique_glyph();


    assert( face            != nullptr &&
            num_load_glyphs >  0 );

    num_glyphs = face->num_glyphs;

    for ( auto  index = 0;
          index < num_glyphs &&
            index < num_load_glyphs;
          index++ )
    {
      LOG( INFO ) << "using glyph " << ( index + 1 ) << "/" << num_glyphs;

      error = FT_Load_Glyph( face.get(), index, load_flags );

      if ( error != 0 )
      {
        LOG( ERROR ) << "FT_Load_Glyph failed: " << error;
        continue; // try the next glyph; it might work better.
      }

      if ( glyph_has_reasonable_work_size(
             get_glyph_from_face( face ) ) == false )
        continue;

      error = FT_Get_Glyph( face->glyph, &raw_glyph );

      if ( error != 0 )
      {
        LOG( ERROR ) << "FT_Get_Glyph failed: " << error;
        continue; // try the next glyph; it might work better.
      }

      glyph = make_unique_glyph( raw_glyph );

      (void) invoke_visitors_and_iterators( glyph );
    }

    WARN_ABOUT_IGNORED_VALUES( num_glyphs, num_load_glyphs, "glyphs" );
  }
