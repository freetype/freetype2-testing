// pfr.cpp
//
//   Implementation of PfrFuzzTarget.
//
// Copyright 2025 by
// The FreeType Project.
//
// This file is part of the FreeType project, and may only be used,
// modified, and distributed under the terms of the FreeType project
// license, LICENSE.TXT.  By continuing to use, modify, or distribute
// this file you indicate that you have read the license and
// understand and accept it fully.


#include "targets/font-drivers/pfr.h"

#include <utility> // std::move

#include "iterators/faceloaditerator.h"
#include "iterators/faceprepiterator-outlines.h"
#include "visitors/facevisitor-pfr.h"
#include "visitors/facevisitor-charcodes.h"
#include "visitors/facevisitor-variants.h"


  freetype::PfrFuzzTarget::
  PfrFuzzTarget()
  {
    auto  fli           = freetype::make_unique<FaceLoadIterator>();
    auto  fpi_outlines  = freetype::make_unique<FacePrepIteratorOutlines>();


    // -----------------------------------------------------------------------
    // Face load iterators:

    (void) fli->set_supported_font_format( FaceLoader::FontFormat::PFR );
    
    (void) fli->add_iterator( std::move( fpi_outlines ) );
    
    (void) fli
      ->add_once_visitor( freetype::make_unique<FaceVisitorPfr>() );
    (void) fli
      ->add_once_visitor( freetype::make_unique<FaceVisitorCharCodes>() );
    (void) fli
      ->add_once_visitor( freetype::make_unique<FaceVisitorVariants>() );

    // -----------------------------------------------------------------------
    // Fuzz target:

    (void) set_iterator( std::move( fli ) );
  }
