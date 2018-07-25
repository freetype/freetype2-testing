// facevisitor-charcodes.h
//
//   Convert char codes to glyph indices and back.
//
//   Drivers: all
//
// Copyright 2018 by
// Armin Hasitzka.
//
// This file is part of the FreeType project, and may only be used,
// modified, and distributed under the terms of the FreeType project
// license, LICENSE.TXT.  By continuing to use, modify, or distribute
// this file you indicate that you have read the license and
// understand and accept it fully.


#ifndef VISITORS_FACE_VISITOR_CHARCODES_H_
#define VISITORS_FACE_VISITOR_CHARCODES_H_

#include <vector>

#include "utils/utils.h"
#include "visitors/facevisitor.h"


  using namespace std;


  class FaceVisitorCharCodes
  : public FaceVisitor
  {
  public:


    FaceVisitorCharCodes( void );


    FaceVisitorCharCodes(
      const FaceVisitorCharCodes& ) = delete;
    FaceVisitorCharCodes& operator= (
      const FaceVisitorCharCodes& ) = delete;


    virtual
    ~FaceVisitorCharCodes( void ) {}


    void
    run( Unique_FT_Face  face )
    override;


  private:

    
    // These operations are cheap but no need to exaggerate:
    static const FT_UInt  SLIDE_ALONG_MAX   = 50;
    static const FT_Int   CHARMAP_INDEX_MAX = 10;

    vector<pair<FT_Encoding, string>>  encodings;


    // @Description:
    //   Drive the `FT_Get_First_Char' and `FT_Get_Next_Char' train for a
    //   while ...
    //
    // @Input:
    //   face ::
    //     The face that will be used for sliding.

    void
    slide_along( const Unique_FT_Face&  face );
  };


#endif // VISITORS_FACE_VISITOR_CHARCODES_H_
