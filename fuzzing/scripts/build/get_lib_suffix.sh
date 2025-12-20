#!/bin/bash
# get_lib_suffix.sh
# Returns the library directory suffix based on CFLAGS.

if [[ "${CFLAGS:-}" == *"-fsanitize=memory"* ]]; then
  echo "lib-msan"
elif [[ "${CFLAGS:-}" == *"-fsanitize=address"* ]]; then
  echo "lib-asan"
elif [[ "${CFLAGS:-}" == *"-fsanitize=undefined"* ]]; then
  echo "lib-ubsan"
else
  echo "lib-asan"
fi
