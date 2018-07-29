// facevisitor-windowsfnt.h
//
//   Retrieve the Windows FNT info header.
//
//   Drivers:
//     - Windows FNT
//
// Copyright 2018 by
// Armin Hasitzka.
//
// This file is part of the FreeType project, and may only be used,
// modified, and distributed under the terms of the FreeType project
// license, LICENSE.TXT.  By continuing to use, modify, or distribute
// this file you indicate that you have read the license and
// understand and accept it fully.


#ifndef VISITORS_FACE_VISITOR_WINDWOS_FNT_H_
#define VISITORS_FACE_VISITOR_WINDWOS_FNT_H_


#include "utils/utils.h"
#include "visitors/facevisitor.h"


  using namespace std;


  class FaceVisitorWindowsFnt
  : public FaceVisitor
  {
  public:


    FaceVisitorWindowsFnt( void ) {}


    FaceVisitorWindowsFnt( const FaceVisitorWindowsFnt& ) = delete;
    FaceVisitorWindowsFnt& operator= (
      const FaceVisitorWindowsFnt& ) = delete;

    
    virtual
    ~FaceVisitorWindowsFnt( void ) {}


    void
    run( Unique_FT_Face  face )
    override;
  };


#endif // VISITORS_FACE_VISITOR_WINDWOS_FNT_H_
