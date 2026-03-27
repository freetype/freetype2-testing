// PropertiesFuzzTarget.h
//
//   Definition of PropertiesFuzzTarget.
//
// Copyright 2025 by
// The FreeType Project.
//
// This file is part of the FreeType project, and may only be used,
// modified, and distributed under the terms of the FreeType project
// license, LICENSE.TXT.  By continuing to use, modify, or distribute
// this file you indicate that you have read the license and
// understand and accept it fully.


#ifndef TARGETS_PROPERTIESFUZZTARGET_H_
#define TARGETS_PROPERTIESFUZZTARGET_H_

#include "targets/FaceFuzzTarget.h"


namespace freetype {

  class PropertiesFuzzTarget
    : public FaceFuzzTarget
  {
  public:
    PropertiesFuzzTarget();
  };

} // namespace freetype

#endif // TARGETS_PROPERTIESFUZZTARGET_H_
