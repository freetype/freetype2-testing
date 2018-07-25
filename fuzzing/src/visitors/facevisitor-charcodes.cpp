// facevisitor-charcodes.cpp
//
//   Implementation of FaceVisitorCharCodes.
//
// Copyright 2018 by
// Armin Hasitzka.
//
// This file is part of the FreeType project, and may only be used,
// modified, and distributed under the terms of the FreeType project
// license, LICENSE.TXT.  By continuing to use, modify, or distribute
// this file you indicate that you have read the license and
// understand and accept it fully.


#include "visitors/facevisitor-charcodes.h"

#include <cassert>

#include "utils/logging.h"


  FaceVisitorCharCodes::
  FaceVisitorCharCodes( void )
  {
    encodings = {
      make_pair( FT_ENCODING_NONE,           "none"           ),
      make_pair( FT_ENCODING_MS_SYMBOL,      "ms symbol"      ),
      make_pair( FT_ENCODING_UNICODE,        "unicode"        ),
      make_pair( FT_ENCODING_SJIS,           "sjis"           ),
      make_pair( FT_ENCODING_PRC,            "prc"            ),
      make_pair( FT_ENCODING_BIG5,           "big5"           ),
      make_pair( FT_ENCODING_WANSUNG,        "wansung"        ),
      make_pair( FT_ENCODING_JOHAB,          "johab"          ),
      make_pair( FT_ENCODING_ADOBE_STANDARD, "adobe standard" ),
      make_pair( FT_ENCODING_ADOBE_EXPERT,   "adobe expert"   ),
      make_pair( FT_ENCODING_ADOBE_CUSTOM,   "adobe custom"   ),
      make_pair( FT_ENCODING_ADOBE_LATIN_1,  "adobe latin 1"  ),
      make_pair( FT_ENCODING_OLD_LATIN_2,    "old latin 2"    ),
      make_pair( FT_ENCODING_APPLE_ROMAN,    "apple roman"    )
    };
  }
  

  void
  FaceVisitorCharCodes::
  run( Unique_FT_Face  face )
  {
    FT_Error  error;


    assert( face != nullptr );

    for ( auto  encoding : encodings )
    {
      error = FT_Select_Charmap( face.get(), encoding.first );

      // No need to log here since this function is expected to fail quite
      // often for arbitrary fonts.  In fact, it would be concerning if this
      // function does not fail at all for a specific font ;)

      if ( error != 0 )
        continue;

      LOG( INFO ) << "charmap exists for encoding: " << encoding.second;

      (void) slide_along( face );
    }

    for ( FT_Int  charmap_index = 0;
          charmap_index < face->num_charmaps &&
            charmap_index < CHARMAP_INDEX_MAX;
          charmap_index++ )
    {
      FT_CharMap charmap = face->charmaps[charmap_index];


      error = FT_Set_Charmap ( face.get(), charmap );

      LOG_IF( ERROR, error != 0 ) << "FT_Set_Charmap failed: " << error;

      if ( error != 0 )
        continue;

      LOG( INFO ) << "load charmap "
                  << ( charmap_index + 1 ) << "/" << face->num_charmaps;

      if ( FT_Get_Charmap_Index( charmap ) != charmap_index )
      {
        LOG( ERROR ) << "FT_Get_Charmap_Index failed";
      }

      (void) slide_along( face );
    }

    WARN_ABOUT_IGNORED_VALUES( face->charmaps,
                               CHARMAP_INDEX_MAX,
                               "character maps" );
  }


  void
  FaceVisitorCharCodes::
  slide_along( const Unique_FT_Face&  face )
  {
    FT_Error  error;

    FT_ULong  char_code;
    FT_UInt   glyph_index;

    FT_String   glyph_name[100];
    FT_UInt     glyph_name_length = 100;

    FT_UInt  slide_index = 0;


    assert( face != nullptr );

    char_code = FT_Get_First_Char( face.get(), &glyph_index );

    while ( glyph_index != 0 )
    {
      if ( slide_index++ >= SLIDE_ALONG_MAX )
      {
        LOG( WARNING ) << "aborted early: more char codes available";
        break;
      }

      if ( glyph_index != FT_Get_Char_Index ( face.get(), char_code ) )
        LOG( ERROR ) << "FT_Get_Char_Index failed";

      // More advanced logic with load flags happens in
      // `FaceVisitorLoadGlyphs*'.  Here, we mainly want to invoke
      // `FT_Load_Char' a few times.

      error = FT_Load_Char( face.get(), char_code, FT_LOAD_DEFAULT );
      LOG_IF( ERROR, error != 0) << "FT_Load_Char failed: " << error;

      if ( FT_HAS_GLYPH_NAMES( face.get() ) != 1 )
      {
        LOG( INFO ) << "char code: " << char_code << ", "
                    << "glyph index: " << glyph_index;
      }
      else
      {
        error = FT_Get_Glyph_Name( face.get(),
                                   glyph_index,
                                   (void*) glyph_name,
                                   glyph_name_length );

        LOG_IF( ERROR, error != 0 ) << "FT_Get_Glyph_Name failed: " << error;

        if ( error != 0 )
          continue;

        if ( glyph_index != FT_Get_Name_Index ( face.get(), glyph_name ) )
          LOG( ERROR ) << "FT_Get_Name_Index failed";
        else
          LOG( INFO ) << "char code: " << char_code << ", "
                      << "glyph index: " << glyph_index << ", "
                      << "name: " << glyph_name;
      }

      char_code = FT_Get_Next_Char( face.get(), char_code, &glyph_index );
    }
  }
