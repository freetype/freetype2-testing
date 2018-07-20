// driver.cpp
//
//   Entry point of the test driver.
//
// Copyright 2018 by
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

#include "targets/font-drivers/cff.h"
#include "targets/font-drivers/cidtype1.h"
#include "targets/font-drivers/truetype.h"
#include "targets/font-drivers/type1.h"
#include "targets/glyphs/outlines.h"
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

#ifdef LOGGER_GLOG
    gflags::ShutDownCommandLineFlags();
#endif // LOGGER_GLOG

    return EXIT_FAILURE;
  }


  int
  print_usage( void )
  {
    return print_error( "\nUsage: driver TYPE FILE\n\n"                 \
                        "Type:\n"                                       \
                        "  --legacy\n"                                  \
                        "  --cff\n"                                     \
                        "  --cidtyp1\n"                                 \
                        "  --truetype\n"                                \
                        "  --type1\n\n"                                 \
                        "  --glyphs-outlines\n\n"                       \
                        "File:\n"                                       \
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
      (void) LLVMFuzzerTestOneInput( data, size );
    else if ( type_arg == "--cff" )
      (void) ( CffFuzzTarget() ).run( data, size );
    else if ( type_arg == "--cidtype1" )
      (void) ( CidType1FuzzTarget() ).run( data, size );
    else if ( type_arg == "--truetype" )
      (void) ( TrueTypeFuzzTarget() ).run( data, size );
    else if ( type_arg == "--type1" )
      (void) ( Type1FuzzTarget() ).run( data, size );
    else if ( type_arg == "--glyphs-outlines" )
      (void) ( GlyphsOutlinesFuzzTarget() ).run( data, size );
    else
      return print_usage();

#ifdef LOGGER_GLOG
    gflags::ShutDownCommandLineFlags();
#endif // LOGGER_GLOG

    return EXIT_SUCCESS;
  }
