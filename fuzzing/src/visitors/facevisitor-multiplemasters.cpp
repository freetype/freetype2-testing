// facevisitor-multiplemasters.cpp
//
//   Implementation of FaceVisitorMultipleMasters.
//
// Copyright 2018 by
// Armin Hasitzka.
//
// This file is part of the FreeType project, and may only be used,
// modified, and distributed under the terms of the FreeType project
// license, LICENSE.TXT.  By continuing to use, modify, or distribute
// this file you indicate that you have read the license and
// understand and accept it fully.


#include "visitors/facevisitor-multiplemasters.h"

#include "utils/logging.h"


  void
  FaceVisitorMultipleMasters::
  run( Unique_FT_Face  face )
  {
    FT_Error  error;

    FT_Library        library;
    FT_MM_Var*        master;
    vector<FT_Fixed>  coords_var_design;
    vector<FT_Fixed>  coords_mm_blend;
    vector<FT_Fixed>  coords_var_blend;


    if ( face == nullptr )
      return;

    if ( FT_HAS_MULTIPLE_MASTERS ( face ) == 0 )
      return;

    library = face->glyph->library;

    error = FT_Get_MM_Var( face.get(), &master );
    if ( error != 0 )
    {
      LOG( ERROR ) << "FT_Get_MM_Var failed: " << error;
      (void) FT_Done_MM_Var( library, master );
      return;
    }

    // Select arbitrary coordinates:
    for ( auto  i = 0; i < master->num_axis; i++ )
    {
      coords_var_design.push_back( ( master->axis[i].minimum +
                                     master->axis[i].def ) / 2 );

      // Each element must be between 0 and 1.0 for Adobe MM fonts, and
      // between -1.0 and 1.0 for TrueType GX and OpenType variation fonts.
      coords_mm_blend.push_back( 0x10000L * 0.5 );
      coords_var_blend.push_back( 0x10000L * 0.5 );
    }

    (void) test_coords( face,
                        coords_var_design,
                        "FT_Set_Var_Design_Coordinates",
                        FT_Set_Var_Design_Coordinates );

    (void) test_coords( face,
                        coords_var_design,
                        "FT_Get_Var_Design_Coordinates",
                        FT_Get_Var_Design_Coordinates );

    (void) test_coords( face,
                        coords_mm_blend,
                        "FT_Set_MM_Blend_Coordinates",
                        FT_Set_MM_Blend_Coordinates );

    (void) test_coords( face,
                        coords_mm_blend,
                        "FT_Get_MM_Blend_Coordinates",
                        FT_Get_MM_Blend_Coordinates );

    (void) test_coords( face,
                        coords_var_blend,
                        "FT_Set_Var_Blend_Coordinates",
                        FT_Set_Var_Blend_Coordinates );

    (void) test_coords( face,
                        coords_var_blend,
                        "FT_Get_Var_Blend_Coordinates",
                        FT_Get_Var_Blend_Coordinates );

    for ( auto  i = 0; i < master->num_axis; i++ )
    {
      FT_UInt flags;


      error = FT_Get_Var_Axis_Flags( master, i, &flags );
      LOG_IF( ERROR, error != 0 )
        << "FT_Get_Var_Axis_Flags failed: " << error;
      LOG_IF( INFO, error == 0 )
        << "flags of axis " << ( i + 1 ) << ": " << hex << flags;
    }

    for ( auto  i = 0; i < master->num_namedstyles; i++ )
    {
      // TODO: extract the name (strid + psid).
      LOG( INFO ) << "setting named instance " << ( i + 1 );
      error = FT_Set_Named_Instance( face.get(), i );
      LOG_IF( ERROR, error != 0 )
        << "FT_Set_Named_Instance failed: " << error;
    }
    
    (void) FT_Done_MM_Var( library, master );
  }


  void
  FaceVisitorMultipleMasters::
  test_coords( Unique_FT_Face&                             face,
               vector<FT_Fixed>&                           coords,
               const string&                               fn_name,
               decltype( FT_Set_Var_Design_Coordinates )*  fn )
  {
    FT_Error  error;


    LOG( INFO ) << "testing " << fn_name;

    error = fn( face.get(), coords.size(), coords.data() );

    LOG_IF( ERROR, error != 0 ) << fn_name << " failed: " << error;
  }