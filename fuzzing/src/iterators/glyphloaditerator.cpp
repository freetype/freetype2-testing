// glyphloaditerator.cpp
//
//   Implementation of GlyphLoadIterator.
//
// Copyright 2018 by
// Armin Hasitzka, David Turner, Robert Wilhelm, and Werner Lemberg.
//
// This file is part of the FreeType project, and may only be used,
// modified, and distributed under the terms of the FreeType project
// license, LICENSE.TXT.  By continuing to use, modify, or distribute
// this file you indicate that you have read the license and
// understand and accept it fully.


#include "iterators/glyphloaditerator.h"

#include "utils/logging.h"


  void
  GlyphLoadIterator::
  add_load_flags( FT_Int32  flags )
  {
    load_flags |= flags;
  }


  void
  GlyphLoadIterator::
  add_visitor( unique_ptr<GlyphVisitor>  visitor )
  {
    (void) glyph_visitors.emplace_back( move( visitor ) );
  }
