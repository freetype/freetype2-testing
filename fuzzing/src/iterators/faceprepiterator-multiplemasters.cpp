// faceprepiterator-multiplemasters.cpp
//
//   Implementation of FacePrepIteratorMultipleMasters.
//
// Copyright 2018 by
// Armin Hasitzka, David Turner, Robert Wilhelm, and Werner Lemberg.
//
// This file is part of the FreeType project, and may only be used,
// modified, and distributed under the terms of the FreeType project
// license, LICENSE.TXT.  By continuing to use, modify, or distribute
// this file you indicate that you have read the license and
// understand and accept it fully.


#include "iterators/faceprepiterator-multiplemasters.h"

#include <glog/logging.h>


  Unique_FT_Face
  FacePrepIteratorMultipleMasters::
  get_prepared_face( const unique_ptr<FaceLoader>&     face_loader,
                     vector<CharSizeTuple>::size_type  index )
  {
    FT_Error  error;

    Unique_FT_Face  face =
      FacePrepIteratorOutlines::get_prepared_face( face_loader, index );

    FT_Library        library;
    FT_MM_Var*        master;
    vector<FT_Fixed>  coords;


    if ( face == nullptr )
      return make_unique_face();

    if ( FT_HAS_MULTIPLE_MASTERS ( face ) == 0 )
      return make_unique_face();

    library = face->glyph->library;

    error = FT_Get_MM_Var( face.get(), &master );
    if ( error != 0 )
    {
      LOG( ERROR ) << "FT_Get_MM_Var failed: " << error;
      return free_and_return( library, master, make_unique_face() );
    }

    // Select arbitrary coordinates:
    for ( auto  i = 0; i < master->num_axis; i++ )
      coords.push_back( ( master->axis[i].minimum +
                          master->axis[i].def ) / 2 );

    error = FT_Set_Var_Design_Coordinates( face.get(),
                                           coords.size(),
                                           coords.data() );
    if ( error != 0 )
    {
      LOG( ERROR) << "FT_Set_Var_Design_Coordinates failed: " << error;
      return free_and_return( library, master, make_unique_face() );
    }

    return free_and_return( library, master, move( face ) );
  }


  Unique_FT_Face
  FacePrepIteratorMultipleMasters::
  free_and_return( FT_Library      library,
                   FT_MM_Var*      master,
                   Unique_FT_Face  face )
  {
    (void) FT_Done_MM_Var( library, master );
    return move( face );
  }
