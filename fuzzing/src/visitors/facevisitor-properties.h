// facevisitor-properties.h
//
//   Definition of FaceVisitorProperties.
//
// Copyright 2025 by
// The FreeType Project.
//
// This file is part of the FreeType project, and may only be used,
// modified, and distributed under the terms of the FreeType project
// license, LICENSE.TXT.  By continuing to use, modify, or distribute
// this file you indicate that you have read the license and
// understand and accept it fully.


#ifndef TARGETS_FACEVISITOR_PROPERTIES_H_
#define TARGETS_FACEVISITOR_PROPERTIES_H_

#include "visitors/facevisitor.h"


namespace freetype {

  class FaceVisitorProperties
    : public FaceVisitor
  {
  public:
    FaceVisitorProperties();

    void
    run( Unique_FT_Face  face ) override;
  };

} // namespace freetype

#endif // TARGETS_FACEVISITOR_PROPERTIES_H_
