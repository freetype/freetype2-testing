// facevisitor-type1tables.cpp
//
//   Implementation of FaceVisitorType1Tables.
//
// Copyright 2018 by
// Armin Hasitzka.
//
// This file is part of the FreeType project, and may only be used,
// modified, and distributed under the terms of the FreeType project
// license, LICENSE.TXT.  By continuing to use, modify, or distribute
// this file you indicate that you have read the license and
// understand and accept it fully.


#include "visitors/facevisitor-type1tables.h"

#include <cassert>

#include <glog/logging.h>

#include <ft2build.h>
#include FT_TYPE1_TABLES_H


  void
  FaceVisitorType1Tables::
  run( Unique_FT_Face  face )
  {
    FT_Error  error;

    FT_Int  has_glyph_names;

    PS_FontInfoRec  font_info_dict;
    PS_PrivateRec   private_dict;


    assert( face.get() != nullptr );

    has_glyph_names = FT_Has_PS_Glyph_Names( face.get() );

    LOG( INFO ) << "postscript glyph names seem to be "
                << ( has_glyph_names == 1 ? "reliable" : "unreliable" );

    // Note: we don't need to retrieve the glyph names here since
    // `FaceVisitorCharCodes' does that for a wide range of faces.  Any face
    // for which `FT_Has_PS_Glyph_Names' returns true will definitely be
    // checked by `FaceVisitorCharCodes'.

    error = FT_Get_PS_Font_Info( face.get(), &font_info_dict );
    
    if ( error == 0 )
      LOG( INFO ) << "retrieved font info dictionary";
    else if ( error == FT_Err_Invalid_Argument )
      LOG( INFO ) << "face is not postscript based";
    else
      LOG( ERROR ) << "FT_Get_PS_Font_Info failed: " << error;

    error = FT_Get_PS_Font_Private( face.get(), &private_dict );
    
    if ( error == 0 )
      LOG( INFO ) << "retrieved private dictionary";
    else if ( error == FT_Err_Invalid_Argument )
      LOG( INFO ) << "face is not postscript based";
    else
      LOG( ERROR ) << "FT_Get_PS_Font_Private failed: " << error;
  }
