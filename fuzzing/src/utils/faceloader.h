// faceloader.h
//
//   Wrapper class to create faces from fuzzed input.
//
// Copyright 2018 by
// Armin Hasitzka.
//
// This file is part of the FreeType project, and may only be used,
// modified, and distributed under the terms of the FreeType project
// license, LICENSE.TXT.  By continuing to use, modify, or distribute
// this file you indicate that you have read the license and
// understand and accept it fully.


#ifndef UTILS_FACE_LOADER_H_
#define UTILS_FACE_LOADER_H_


#include <string>
#include <vector>

#include "utils/tarreader.h"
#include "utils/utils.h"


  using namespace fuzzing;
  using namespace std;


  class FaceLoader
  {
  public:

    
    enum class FontFormat
      : unsigned char
    {
      NONE,
      BDF,
      CID_TYPE_1,
      CFF,
      PCF,
      PFR,
      TRUETYPE,
      TYPE_1,
      TYPE_42,
      WINDOWS_FNT
    };


    FaceLoader( void )
      : tarreader( files ) {}


    FaceLoader( const FaceLoader& ) = delete;
    FaceLoader& operator= ( const FaceLoader& ) = delete;


    // @Description:
    //   Set the supported font format / font driver.  This face loader will
    //   only load faces which are of the specified font format / require the
    //   specified font driver.
    //
    // @Input:
    //   format ::
    //     Use one of the predefined formats.  Setting the format `NONE' will
    //     result in this face loader rejecting every possible input.

    void
    set_supported_font_format( FontFormat  format );
    
    
    // @Description:
    //   Set the FreeType library that drives font face creation.
    //
    // @Input:
    //   library ::
    //     A library that is initialised already.

    void
    set_library( FT_Library  library );


    // @Description:
    //   Set the raw bytes that are interpreted as a font file or an archive
    //   of files that descript a specific font (e.g. used by Type 1 fonts).
    //
    // @Input:
    //   data ::
    //     ...
    //
    //   size ::
    //     ...

    void
    set_raw_bytes( const uint8_t*  data,
                   size_t          size );


    // @Description:
    //   Tries to interpret fuzzing data as tar archives if `true'.  If the
    //   input data can somehow be opened by libarchve, it will be used that
    //   way, otherwise the input gets interpreted as a single input file.
    //   Note: only enable this if needed since it adds a considerable (and
    //   unnecessary) overhead when not needed.
    //
    // @Input:
    //   accept ::
    //     Try to interpret fuzzing input as tar archives if `true'. Skip that
    //     step if `false'.  Default: `false'.

    void
    set_accept_tar_archives( bool  accept );


    void
    set_face_index( FT_Long  index );

    
    void
    set_instance_index( FT_Long  index );

        
    // @Description:
    //   Returns the amount of faces that could be loaded according to the
    //   input bytes.  Mind: not every font might be valid.
    //
    // @Return:
    //   The number of faces.

    FT_Long
    get_num_faces( void );


    FT_Long
    get_num_instances( void );
      

    // @Description:
    //   Tries to load the specified face from memory and verifies driver.
    //
    // @Input:
    //   face_index ::
    //     Index of the face that should be loaded.
    //     see: https://www.freetype.org/freetype2/docs/reference/
    //          ft2-base_interface.html#FT_Open_Face
    //
    //   instance_index ::
    //     ...
    //
    // @Return:
    //   A pointer to a face object or nullptr if any error occurred.

    Unique_FT_Face
    load( void );


  private:


    FT_Library  library = nullptr;
    
    TarReader  tarreader;

    vector<vector<FT_Byte>>  files;

    FontFormat  supported_font_format        = FontFormat::NONE;
    string      supported_font_format_string = "";

    bool  accept_tar_archives = false;

    FT_Long  num_faces  = -1;
    FT_Long  face_index =  0;

    FT_Long  num_instances  = -1;
    FT_Long  instance_index =  0;


    Unique_FT_Face
    load_face( FT_Long  face_index     = -1,
               FT_Long  instance_inces =  0 );
  };


#endif // UTILS_FACE_LOADER_H_
