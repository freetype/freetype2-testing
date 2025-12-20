// facevisitor-pfr.cpp
//
//   Implementation of FaceVisitorPfr.
//
// Copyright 2025 by
// The FreeType Project.
//
// This file is part of the FreeType project, and may only be used,
// modified, and distributed under the terms of the FreeType project
// license, LICENSE.TXT.  By continuing to use, modify, or distribute
// this file you indicate that you have read the license and
// understand and accept it fully.


#include "visitors/facevisitor-pfr.h"

#include <cassert>

#include <ft2build.h>
#include FT_PFR_H

#include "utils/logging.h"


  freetype::FaceVisitorPfr::
  FaceVisitorPfr()
  {
  }


  void
  freetype::FaceVisitorPfr::
  run( Unique_FT_Face  face )
  {
    FT_Error     error;
    FT_UInt      outline_res;
    FT_UInt      metrics_res;
    FT_Fixed     metrics_x_scale;
    FT_Fixed     metrics_y_scale;

    assert( face != nullptr );

    // Check PFR Metrics
    error = FT_Get_PFR_Metrics( face.get(),
                                &outline_res,
                                &metrics_res,
                                &metrics_x_scale,
                                &metrics_y_scale );
    LOG_FT_ERROR( "FT_Get_PFR_Metrics", error );
    
    if ( error == 0 )
    {
      LOG( INFO ) << "PFR Metrics: "
                  << "outline_res=" << outline_res << ", "
                  << "metrics_res=" << metrics_res;
    }

    // Check PFR Advance
    // Test first 50, last 50, and some invalid indices
    std::vector<FT_UInt> indices_to_test;
    
    FT_Long num_glyphs = face->num_glyphs;
    
    for ( FT_Long i = 0; i < 50 && i < num_glyphs; i++ )
      indices_to_test.push_back( (FT_UInt)i );
      
    if ( num_glyphs > 50 ) {
      for ( FT_Long i = num_glyphs - 50; i < num_glyphs; i++ )
        if ( i >= 50 ) indices_to_test.push_back( (FT_UInt)i );
    }
    
    // Invalid indices
    indices_to_test.push_back( (FT_UInt)num_glyphs );
    indices_to_test.push_back( (FT_UInt)num_glyphs + 100 );
    indices_to_test.push_back( 0xFFFF );

    for ( FT_UInt idx : indices_to_test )
    {
      FT_Pos  advance;
      error = FT_Get_PFR_Advance( face.get(), idx, &advance );
      // We expect errors for invalid indices, so just log debug or ignore
      if ( error ) 
        LOG_FT_ERROR( "FT_Get_PFR_Advance", error );
    }

    // Check PFR Kerning
    // Test a subset of pairs from the indices list
    // To avoid O(N^2) on the full list, just pick a few combinations
    for ( size_t i = 0; i < indices_to_test.size(); i++ )
    {
        // Test against itself and the next one
        FT_UInt left = indices_to_test[i];
        FT_UInt right1 = indices_to_test[i];
        FT_UInt right2 = indices_to_test[(i + 1) % indices_to_test.size()];
        
        FT_Vector kerning;
        error = FT_Get_PFR_Kerning( face.get(), left, right1, &kerning );
        if ( error ) LOG_FT_ERROR( "FT_Get_PFR_Kerning", error );

        error = FT_Get_PFR_Kerning( face.get(), left, right2, &kerning );
        if ( error ) LOG_FT_ERROR( "FT_Get_PFR_Kerning", error );
    }
  }
