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

#include <cassert>
#include <cmath>
#include <limits>
#include <set>

#include <ft2build.h>
#include FT_OUTLINE_H

#include "utils/logging.h"


  FaceVisitorLoadGlyphs::
  FaceVisitorLoadGlyphs( void )
  {
    (void) add_transformation( nullptr, nullptr );
  }


  void
  FaceVisitorLoadGlyphs::
  run( Unique_FT_Face  face )
  {
    FT_Error  error;

    FT_Long  num_glyphs;

    FT_GlyphSlot  glyph_slot;
    FT_BBox       control_box;
    FT_Pos        width;
    FT_Pos        width_max = numeric_limits<decltype( width )>::max();
    FT_Pos        height;

    assert( face != nullptr );

    num_glyphs = face->num_glyphs;

    for ( auto  transformation : transformations )
    {
      FT_Matrix*  matrix = transformation.first;
      FT_Vector*  vector = transformation.second;


      LOG_IF( INFO, matrix == nullptr ) << "setting transformation matrix: none";
      LOG_IF( INFO, matrix != nullptr )
        << "setting transformation matrix: "
        << matrix->xx << ", " << matrix->xy << "; "
        << matrix->yx << ", " << matrix->yy;

      LOG_IF( INFO, vector == nullptr ) << "setting transform vector: none";
      LOG_IF( INFO, vector != nullptr )
        << "setting transform vector: "
        << vector->x << ", " << vector->y;

      (void) FT_Set_Transform( face.get(), matrix, vector );

      for ( auto  index = 0;
            index < num_glyphs &&
              index < GLYPH_INDEX_MAX;
            index++ )
      {
        LOG( INFO ) << "testing glyph " << ( index + 1 ) << "/" << num_glyphs;

        for ( auto  load_flags : this->load_flags )
        {
          LOG( INFO ) << "load flags: " << hex << "0x" << load_flags;

          glyph_slot = face->glyph;

          if ( glyph_slot->format == FT_GLYPH_FORMAT_OUTLINE )
          {
            (void) FT_Outline_Get_CBox( &glyph_slot->outline,
                                        &control_box );

            width  = abs( control_box.xMin - control_box.xMax );
            height = abs( control_box.yMin - control_box.yMax );

            LOG( INFO ) << "glyph size: "
                        << width << " x " << height << "\n";

            // Don't forget to check for overflows first!

            if ( width  > 0 &&
                 height > 0 &&
                 ( width_max / width < height ||
                   width * height > RENDER_PIXELS_MAX ) )
            {
              LOG( WARNING ) << "glyph too large to be rendered";
              continue;
            }
          }

          error = FT_Load_Glyph( face.get(), index, load_flags );

          LOG_IF( ERROR, error != 0 ) << "FT_Load_Glyph failed: " << error;
        }
      }

      WARN_ABOUT_IGNORED_VALUES( num_glyphs, GLYPH_INDEX_MAX, "glyphs" );
    }
  }


  void
  FaceVisitorLoadGlyphs::
  add_transformation( FT_Matrix*  matrix,
                      FT_Vector*  delta )
  {
    (void) transformations.push_back( { matrix, delta } );
  }


  void
  FaceVisitorLoadGlyphs::
  add_load_flags( FT_Int32  flags )
  {
    (void) load_flags.push_back( flags );
  }
