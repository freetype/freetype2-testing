// pfr.h
//
//   Fuzz PFR faces.
//
// Copyright 2025 by
// The FreeType Project.
//
// This file is part of the FreeType project, and may only be used,
// modified, and distributed under the terms of the FreeType project
// license, LICENSE.TXT.  By continuing to use, modify, or distribute
// this file you indicate that you have read the license and
// understand and accept it fully.


#ifndef TARGETS_FONT_DRIVERS_PFR_H_
#define TARGETS_FONT_DRIVERS_PFR_H_


#include "targets/FaceFuzzTarget.h"


namespace freetype {


  class PfrFuzzTarget
    : public FaceFuzzTarget
  {
  public:


    PfrFuzzTarget();
  };
}


#endif // TARGETS_FONT_DRIVERS_PFR_H_
