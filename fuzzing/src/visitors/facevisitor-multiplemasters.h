// facevisitor-multiplemasters.h
//
//   Play with multiple masters;  more intensively than
//   FacePrepIteratorMultipleMasters.
//
//   Drivers:
//     - CFF
//     - TrueType
//     - Type 1
//
// Copyright 2018 by
// Armin Hasitzka.
//
// This file is part of the FreeType project, and may only be used,
// modified, and distributed under the terms of the FreeType project
// license, LICENSE.TXT.  By continuing to use, modify, or distribute
// this file you indicate that you have read the license and
// understand and accept it fully.


#ifndef VISITORS_FACE_VISITOR_MULTIPLE_MASTERS_H_
#define VISITORS_FACE_VISITOR_MULTIPLE_MASTERS_H_

#include <vector>

#include <ft2build.h>
#include FT_MULTIPLE_MASTERS_H

#include "utils/utils.h"
#include "visitors/facevisitor.h"


  using namespace std;


  class FaceVisitorMultipleMasters
  : public FaceVisitor
  {
  public:


    FaceVisitorMultipleMasters( void ) {}


    FaceVisitorMultipleMasters(
      const FaceVisitorMultipleMasters& ) = delete;
    FaceVisitorMultipleMasters& operator= (
      const FaceVisitorMultipleMasters& ) = delete;


    virtual
    ~FaceVisitorMultipleMasters( void ) {}


    void
    run( Unique_FT_Face  face )
    override;


  private:


    // @Description:
    //   Apply `coords' to `fn'.
    // 
    // @Input:
    //   face ::
    //     A font face.
    //   coords ::
    //     A vector that will be applied to `fn'.
    //   fn_name ::
    //     A string that contains the name of `fn'.
    //   fn ::
    //     A function that `coords' will be applied to.

    void
    test_coords( Unique_FT_Face&                             face,
                 vector<FT_Fixed>&                           coords,
                 const string&                               fn_name,
                 decltype( FT_Set_Var_Design_Coordinates )*  fn );
  };


#endif // VISITORS_FACE_VISITOR_MULTIPLE_MASTERS_H_
