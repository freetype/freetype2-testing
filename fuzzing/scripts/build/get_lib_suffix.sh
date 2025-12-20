#!/bin/bash
# get_lib_suffix.sh
# Returns the library directory suffix based on CFLAGS.

if [[ "${CFLAGS:-}" == *"-fsanitize=memory"* ]]; then
  echo "lib-msan"
else
  echo "lib-asan"
fi
