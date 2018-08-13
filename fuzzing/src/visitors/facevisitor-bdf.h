// facevisitor-bdf.h
//
//   Check BDF specific API functions.
//
//   Drivers:
//     - BDF
//     - PCF
//
// Copyright 2018 by
// Armin Hasitzka.
//
// This file is part of the FreeType project, and may only be used,
// modified, and distributed under the terms of the FreeType project
// license, LICENSE.TXT.  By continuing to use, modify, or distribute
// this file you indicate that you have read the license and
// understand and accept it fully.


#ifndef VISITORS_FACE_VISITOR_BDF_H_
#define VISITORS_FACE_VISITOR_BDF_H_


#include "utils/faceloader.h"
#include "utils/utils.h"
#include "visitors/facevisitor.h"


  using namespace std;


  class FaceVisitorBdf
  : public FaceVisitor
  {
  public:


    FaceVisitorBdf( FaceLoader::FontFormat  format );


    FaceVisitorBdf( const FaceVisitorBdf& ) = delete;
    FaceVisitorBdf& operator= ( const FaceVisitorBdf& ) = delete;

    
    virtual
    ~FaceVisitorBdf( void ) {}


    void
    run( Unique_FT_Face  face )
    override;


  private:


    FaceLoader::FontFormat  font_format;
  };


#endif // VISITORS_FACE_VISITOR_BDF_H_
