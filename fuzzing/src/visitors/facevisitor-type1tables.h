// facevisitor-type1tables.h
//
//   Access Type 1 tables.  Note: for Multiple Master fonts, each instance has
//   its own dictionaries.
//
//   Drivers:
//     - CFF
//     - CID Type 1
//     - Type 1
//     - Type 42
//
// Copyright 2018 by
// Armin Hasitzka.
//
// This file is part of the FreeType project, and may only be used,
// modified, and distributed under the terms of the FreeType project
// license, LICENSE.TXT.  By continuing to use, modify, or distribute
// this file you indicate that you have read the license and
// understand and accept it fully.


#ifndef VISITORS_FACE_VISITOR_TYPE_1_TABLES_H_
#define VISITORS_FACE_VISITOR_TYPE_1_TABLES_H_


#include "utils/utils.h"
#include "visitors/facevisitor.h"


  using namespace std;


  class FaceVisitorType1Tables
  : public FaceVisitor
  {
  public:


    FaceVisitorType1Tables( void ) {}


    FaceVisitorType1Tables( const FaceVisitorType1Tables& ) = delete;
    FaceVisitorType1Tables& operator= (
      const FaceVisitorType1Tables& ) = delete;


    virtual
    ~FaceVisitorType1Tables( void ) {}


    void
    run( Unique_FT_Face  face )
    override;
  };


#endif // VISITORS_FACE_VISITOR_TYPE_1_TABLES_H_
