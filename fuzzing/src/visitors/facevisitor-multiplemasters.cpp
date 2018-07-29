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

#include "utils/faceloader.h"
#include "utils/logging.h"


  FaceVisitorMultipleMasters::
  FaceVisitorMultipleMasters( FaceLoader::FontFormat  format )
  {
    has_adobe_mm = format == FaceLoader::FontFormat::TYPE_1 ? true : false;
  }


  void
  FaceVisitorMultipleMasters::
  run( Unique_FT_Face  face )
  {
    FT_Error  error;

    FT_Library       library;
    FT_Multi_Master  master;
    FT_MM_Var*       var;

    vector<FT_Long>   coords_mm_design;
    vector<FT_Fixed>  coords_var_design;
    vector<FT_Fixed>  coords_mm_blend;
    vector<FT_Fixed>  coords_var_blend;


    if ( face == nullptr )
      return;

    if ( FT_HAS_MULTIPLE_MASTERS( face ) == 0 )
      return;

    library = face->glyph->library;

    if ( has_adobe_mm == true )
    {
      error = FT_Get_Multi_Master( face.get(), &master );
      LOG_IF( ERROR, error != 0 ) << "FT_Get_Multi_Master failed: " << error;

      if ( error == 0 )
      {
        for ( auto i = 0; i < master.num_axis; i++ )
        {
          coords_mm_design.push_back( ( master.axis[i].minimum +
                                        master.axis[i].maximum ) / 2 );
        }

        LOG( INFO ) << "testing FT_Set_MM_Design_Coordinates";

        error = FT_Set_MM_Design_Coordinates( face.get(),
                                              coords_mm_design.size(),
                                              coords_mm_design.data() );
        LOG_IF( ERROR, error != 0 )
          << "FT_Set_MM_Design_Coordinates failed: " << error;
      }
    }

    error = FT_Get_MM_Var( face.get(), &var );
    if ( error != 0 )
    {
      LOG( ERROR ) << "FT_Get_MM_Var failed: " << error;
      (void) FT_Done_MM_Var( library, var );
      return;
    }

    // Select arbitrary coordinates:
    for ( auto  i = 0;
          i < var->num_axis &&
            i < AXIS_INDEX_MAX;
          i++ )
    {
      coords_var_design.push_back( ( var->axis[i].minimum +
                                     var->axis[i].def ) / 2 );

      // Each element must be between 0 and 1.0 for Adobe MM fonts, and
      // between -1.0 and 1.0 for TrueType GX and OpenType variation fonts.
      coords_mm_blend.push_back( 0x10000L * 0.5 );
      coords_var_blend.push_back( 0x10000L * 0.5 );
    }

    WARN_ABOUT_IGNORED_VALUES( var->num_axis, AXIS_INDEX_MAX, "axis" );

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

    for ( auto  i = 0; i < var->num_axis; i++ )
    {
      FT_UInt flags;


      error = FT_Get_Var_Axis_Flags( var, i, &flags );
      LOG_IF( ERROR, error != 0 )
        << "FT_Get_Var_Axis_Flags failed: " << error;
      LOG_IF( INFO, error == 0 )
        << "flags of axis " << ( i + 1 ) << ": " << hex << "0x" << flags;
    }

    for ( auto  i = 0; i < var->num_namedstyles; i++ )
    {
      // TODO: extract the name (strid + psid).
      LOG( INFO ) << "setting named instance " << ( i + 1 );
      error = FT_Set_Named_Instance( face.get(), i );
      LOG_IF( ERROR, error != 0 )
        << "FT_Set_Named_Instance failed: " << error;
    }
    
    (void) FT_Done_MM_Var( library, var );
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
