// facevisitor-variants.h
//
//   Play with unicode variation sequences.
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


#ifndef VISITORS_FACE_VISITOR_VARIANTS_H_
#define VISITORS_FACE_VISITOR_VARIANTS_H_


#include "utils/utils.h"
#include "visitors/facevisitor.h"


  using namespace std;


  class FaceVisitorVariants
  : public FaceVisitor
  {
  public:


    FaceVisitorVariants( void ) {}


    FaceVisitorVariants( const FaceVisitorVariants& ) = delete;
    FaceVisitorVariants& operator= ( const FaceVisitorVariants& ) = delete;


    virtual
    ~FaceVisitorVariants( void ) {}


    void
    run( Unique_FT_Face  face )
    override;
  };


#endif // VISITORS_FACE_VISITOR_VARIANTS_H_
