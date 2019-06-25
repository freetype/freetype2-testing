// driver.cpp
//
//   Entry point of the test driver.
//
// Copyright 2019 by
// Armin Hasitzka.
//
// This file is part of the FreeType project, and may only be used,
// modified, and distributed under the terms of the FreeType project
// license, LICENSE.TXT.  By continuing to use, modify, or distribute
// this file you indicate that you have read the license and
// understand and accept it fully.


#include <cstdlib>
#include <fstream>
#include <iostream>
#include <vector>

#include "targets/font-drivers/bdf.h"
#include "targets/font-drivers/bdf-render.h"

#include "targets/font-drivers/cff.h"
#include "targets/font-drivers/cff-ftengine.h"
#include "targets/font-drivers/cff-render.h"
#include "targets/font-drivers/cff-render-ftengine.h"

#include "targets/font-drivers/cidtype1.h"
#include "targets/font-drivers/cidtype1-ftengine.h"
#include "targets/font-drivers/cidtype1-render.h"
#include "targets/font-drivers/cidtype1-render-ftengine.h"

#include "targets/font-drivers/pcf.h"
#include "targets/font-drivers/pcf-render.h"

#include "targets/font-drivers/truetype.h"
#include "targets/font-drivers/truetype-render.h"
#include "targets/font-drivers/truetype-render-i35.h"
#include "targets/font-drivers/truetype-render-i38.h"

#include "targets/font-drivers/type1.h"
#include "targets/font-drivers/type1-ftengine.h"
#include "targets/font-drivers/type1-render.h"
#include "targets/font-drivers/type1-render-ftengine.h"
#include "targets/font-drivers/type1-render-tar.h"
#include "targets/font-drivers/type1-tar.h"

#include "targets/font-drivers/type42.h"
#include "targets/font-drivers/type42-render.h"

#include "targets/font-drivers/windowsfnt.h"
#include "targets/font-drivers/windowsfnt-render.h"

#include "targets/glyphs/outlines.h"
#include "targets/glyphs/bitmaps-pcf.h"

#include "targets/support/Bzip2FuzzTarget.h"
#include "targets/support/GzipFuzzTarget.h"
#include "targets/support/LzwFuzzTarget.h"

#include "utils/logging.h"


  using namespace std;


  // The legacy fuzzer is a monolith but it is the only target that calls
  // LLVMFuzzerTestOneInput( ... ) directly which is why we get away with
  // using it to invoke the legacy target.

  extern "C" int
  LLVMFuzzerTestOneInput( const uint8_t*  data,
                          size_t          size );


  int
  print_error( const string&  message )
  {
    cerr << message << "\n";

    return EXIT_FAILURE;
  }


  int
  print_usage( void )
  {
    return print_error( "\nUsage: driver TYPE FILE\n\n"                 \
                        "Type:\n\n"                                     \
                        "  --legacy\n\n"                                \
                        "  --bdf\n"                                     \
                        "  --bdf-render\n\n"                            \
                        "  --cff\n"                                     \
                        "  --cff-ftengine\n"                            \
                        "  --cff-render\n"                              \
                        "  --cff-render-ftengine\n\n"                   \
                        "  --cidtype1\n"                                \
                        "  --cidtype1-ftengine\n"                       \
                        "  --cidtype1-render\n"                         \
                        "  --cidtype1-render-ftengine\n\n"              \
                        "  --pcf\n"                                     \
                        "  --pcf-render\n\n"                            \
                        "  --truetype\n"                                \
                        "  --truetype-render\n"                         \
                        "  --truetype-render-i35\n"                     \
                        "  --truetype-render-i38\n\n"                   \
                        "  --type1\n"                                   \
                        "  --type1-ftengine\n"                          \
                        "  --type1-render\n"                            \
                        "  --type1-render-ftengine\n"                   \
                        "  --type1-render-tar\n"                        \
                        "  --type1-tar\n\n"                             \
                        "  --type42\n"                                  \
                        "  --type42-render\n\n"                         \
                        "  --windowsfnt\n"                              \
                        "  --windowsfnt-render\n\n"                     \
                        "  --glyphs-outlines\n\n"                       \
                        "  --glyphs-bitmaps-pcf\n\n"                    \
                        "  --gzip\n"                                    \
                        "  --lzw\n"                                     \
                        "  --bzip2\n\n"                                 \
                        "File:\n\n"                                     \
                        "  The location (path) of an input file.\n" );
  }


  int
  main( int     argc,
        char**  argv )
  {

#ifdef LOGGER_GLOG
  (void) google::InitGoogleLogging( argv[0] );
#endif // LOGGER_GLOG

    if ( argc != 3 )
      return print_usage();

    string  input_file_arg( argv[2] );

    ifstream  input_file( input_file_arg, ios_base::binary );
    if ( input_file.is_open() == false )
      return print_error( "error: invalid file '" + input_file_arg + "'");

    vector<char>  input( ( istreambuf_iterator<char>( input_file ) ),
                         istreambuf_iterator<char>() );

    (void) input_file.close();

    uint8_t*  data = reinterpret_cast<uint8_t*>( input.data() );
    size_t    size = input.size();

    string  type_arg( argv[1] );

    if ( type_arg == "--legacy" )
      (void) LLVMFuzzerTestOneInput(                     data, size );

    else if ( type_arg == "--bdf" )
      (void) ( BdfFuzzTarget()                    ).run( data, size );
    else if ( type_arg == "--bdf-render" )
      (void) ( BdfRenderFuzzTarget()              ).run( data, size );

    else if ( type_arg == "--cff" )
      (void) ( CffFuzzTarget()                    ).run( data, size );
    else if ( type_arg == "--cff-ftengine" )
      (void) ( CffFtEngineFuzzTarget()            ).run( data, size );
    else if ( type_arg == "--cff-render" )
      (void) ( CffRenderFuzzTarget()              ).run( data, size );
    else if ( type_arg == "--cff-render-ftengine" )
      (void) ( CffRenderFtEngineFuzzTarget()      ).run( data, size );

    else if ( type_arg == "--cidtype1" )
      (void) ( CidType1FuzzTarget()               ).run( data, size );
    else if ( type_arg == "--cidtype1-ftengine" )
      (void) ( CidType1FtEngineFuzzTarget()       ).run( data, size );
    else if ( type_arg == "--cidtype1-render" )
      (void) ( CidType1RenderFuzzTarget()         ).run( data, size );
    else if ( type_arg == "--cidtype1-render-ftengine" )
      (void) ( CidType1RenderFtEngineFuzzTarget() ).run( data, size );

    else if ( type_arg == "--pcf" )
      (void) ( PcfFuzzTarget()                    ).run( data, size );
    else if ( type_arg == "--pcf-render" )
      (void) ( PcfRenderFuzzTarget()              ).run( data, size );

    else if ( type_arg == "--truetype" )
      (void) ( TrueTypeFuzzTarget()               ).run( data, size );
    else if ( type_arg == "--truetype-render" )
      (void) ( TrueTypeRenderFuzzTarget()         ).run( data, size );
    else if ( type_arg == "--truetype-render-i35" )
      (void) ( TrueTypeRenderI35FuzzTarget()      ).run( data, size );
    else if ( type_arg == "--truetype-render-i38" )
      (void) ( TrueTypeRenderI38FuzzTarget()      ).run( data, size );

    else if ( type_arg == "--type1" )
      (void) ( Type1FuzzTarget()                  ).run( data, size );
    else if ( type_arg == "--type1-ftengine" )
      (void) ( Type1FtEngineFuzzTarget()          ).run( data, size );
    else if ( type_arg == "--type1-render" )
      (void) ( Type1RenderFuzzTarget()            ).run( data, size );
    else if ( type_arg == "--type1-render-ftengine" )
      (void) ( Type1RenderFtEngineFuzzTarget()    ).run( data, size );
    else if ( type_arg == "--type1-render-tar" )
      (void) ( Type1RenderTarFuzzTarget()         ).run( data, size );
    else if ( type_arg == "--type1-tar" )
      (void) ( Type1TarFuzzTarget()               ).run( data, size );

    else if ( type_arg == "--type42" )
      (void) ( Type42FuzzTarget()                 ).run( data, size );
    else if ( type_arg == "--type42-render" )
      (void) ( Type42RenderFuzzTarget()           ).run( data, size );

    else if ( type_arg == "--windowsfnt" )
      (void) ( WindowsFntFuzzTarget()             ).run( data, size );
    else if ( type_arg == "--windowsfnt-render" )
      (void) ( WindowsFntRenderFuzzTarget()       ).run( data, size );

    else if ( type_arg == "--glyphs-outlines" )
      (void) ( GlyphsOutlinesFuzzTarget()         ).run( data, size );

    else if ( type_arg == "--glyphs-bitmaps-pcf" )
      (void) ( GlyphsBitmapsPcfFuzzTarget()       ).run( data, size );

    else if ( type_arg == "--gzip" )
      (void) ( freetype::GzipFuzzTarget()         ).run( data, size );
    else if ( type_arg == "--lzw" )
      (void) ( freetype::LzwFuzzTarget()          ).run( data, size );
    else if ( type_arg == "--bzip2" )
      (void) ( freetype::Bzip2FuzzTarget()        ).run( data, size );

    else
      return print_usage();

    return EXIT_SUCCESS;
  }
