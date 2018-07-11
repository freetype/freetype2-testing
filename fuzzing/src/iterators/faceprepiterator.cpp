// faceprepiterator.cpp
//
//   Implementation of FacePrepIterator.
//
// Copyright 2018 by
// Armin Hasitzka, David Turner, Robert Wilhelm, and Werner Lemberg.
//
// This file is part of the FreeType project, and may only be used,
// modified, and distributed under the terms of the FreeType project
// license, LICENSE.TXT.  By continuing to use, modify, or distribute
// this file you indicate that you have read the license and
// understand and accept it fully.


#include "iterators/faceprepiterator.h"

#include <ft2build.h>
#include FT_FREETYPE_H

#include "utils/logging.h"


  void
  FacePrepIterator::
  add_visitor( unique_ptr<FaceVisitor>  visitor )
  {
    (void) face_visitors.emplace_back( move( visitor ) );
  }


  void
  FacePrepIterator::
  add_iterator( unique_ptr<GlyphLoadIterator>  iterator )
  {
    (void) glyph_load_iterators.emplace_back( move( iterator ) );
  }
