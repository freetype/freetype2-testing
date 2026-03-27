// facevisitor-pfr.h
//
//   Check PFR specific API functions.
//
//   Drivers:
//     - PFR
//
// Copyright 2025 by
// The FreeType Project.
//
// This file is part of the FreeType project, and may only be used,
// modified, and distributed under the terms of the FreeType project
// license, LICENSE.TXT.  By continuing to use, modify, or distribute
// this file you indicate that you have read the license and
// understand and accept it fully.


#ifndef VISITORS_FACE_VISITOR_PFR_H_
#define VISITORS_FACE_VISITOR_PFR_H_


#include "utils/faceloader.h"
#include "utils/utils.h"
#include "visitors/facevisitor.h"


namespace freetype {


  class FaceVisitorPfr
    : public FaceVisitor
  {
  public:

    FaceVisitorPfr();

    void
    run( Unique_FT_Face  face )
    override;

  };
}


#endif // VISITORS_FACE_VISITOR_PFR_H_
