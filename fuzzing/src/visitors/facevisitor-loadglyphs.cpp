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
#include <set>

#include "utils/logging.h"


  FaceVisitorLoadGlyphs::
  FaceVisitorLoadGlyphs( FT_Long  num_used_glyphs )
  {
    (void) add_transformation( nullptr, nullptr );
    (void) set_num_used_glyphs( num_used_glyphs );
  }


  void
  FaceVisitorLoadGlyphs::
  run( Unique_FT_Face  face )
  {
    FT_Error  error;
    FT_Long   num_glyphs;


    assert( face            != nullptr &&
            num_used_glyphs >  0 );

    num_glyphs = face->num_glyphs;

    for ( auto  transformation : transformations )
    {
      FT_Matrix*  matrix = transformation.first;
      FT_Vector*  vector = transformation.second;


      LOG_IF( INFO, matrix == nullptr )
        << "setting transformation matrix: none";
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
              index < num_used_glyphs;
            index++ )
      {
        LOG( INFO ) << "testing glyph " << ( index + 1 ) << "/" << num_glyphs;

        for ( auto mode : modes )
        {
          LOG( INFO ) << "load flags: 0x" << hex << get<0>( mode );

          error = FT_Load_Glyph( face.get(), index, get<0>( mode ) );

          if ( error != 0 )
          {
            LOG( ERROR ) << "FT_Load_Glyph failed: " << error;
            continue;
          }

          if ( get<1>( mode ) == false )
            continue;

          if ( glyph_has_reasonable_render_size(
                 get_glyph_from_face( face ) ) == false )
            continue;

          LOG( INFO ) << "render mode: 0x" << hex << get<2>( mode );

          error = FT_Render_Glyph( face->glyph, get<2>( mode ) );

          LOG_IF( ERROR, error != 0 ) << "FT_Render_Glyph failed: " << error;
        }
      }

      WARN_ABOUT_IGNORED_VALUES( num_glyphs, num_used_glyphs, "glyphs" );
    }
  }


  void
  FaceVisitorLoadGlyphs::
  set_num_used_glyphs( FT_Long  max )
  {
    num_used_glyphs = max;
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
  add_mode( FT_Int32        load_flags )
  {
    (void) modes.push_back( ModeTuple( load_flags,
                                       false,
                                       FT_RENDER_MODE_NORMAL ) );
  }


  void
  FaceVisitorLoadGlyphs::
  add_mode( FT_Int32        load_flags,
            FT_Render_Mode  render_mode )
  {
    (void) modes.push_back( ModeTuple( load_flags, true, render_mode ) );
  }
