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

    FT_Long  num_glyphs = face->num_glyphs;


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
