#!/usr/bin/bash

EXIT_CODE=13

if [ -f bush ]; then
  rm bush
fi


if [ -x "$(command -v clang)" ]; then
  clang -Wall -Werror -pedantic -std=gnu2x ./src/*.c -o bush
else
  if [ -x "$(command -v gcc)" ]; then
    gcc -Wall -Werror -pedantic -std=gnu2x ./src/*.c -o bush
  else
    echo -e "clang and gcc compilers not found in your system. Please compile manually.\n"
    exit "$EXIT_CODE"
  fi
fi


if [ ! -f bush ]; then
  exit "$EXIT_CODE"
fi
