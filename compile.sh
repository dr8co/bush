#!/bin/bash

# Default standards
CLANG_VERSION=4
GCC_VERSION=3

# Function to set standard compilation flag
set_std_flag() {
  if [ "$CLANG_VERSION" -ge 10 ] || [ "$GCC_VERSION" -ge 10 ]; then
    C_STD="-std=gnu2x"
  elif [ "$CLANG_VERSION" -ge 8 ] || [ "$GCC_VERSION" -ge 7 ]; then
    C_STD="-std=gnu17"
  elif [ "$CLANG_VERSION" -ge 5 ] || [ "$GCC_VERSION" -ge 4 ]; then
    C_STD="-std=gnu11"
  else
    C_STD="-std=gnu99"
  fi
}

EXIT_CODE=13

if [ -f bush ]; then
  rm bush
fi

if [ -x "$(command -v clang)" ]; then
  CLANG_VERSION=$(clang --version | grep -n 1 | awk '{split($4, ver, "."); print ver[1]}')
  set_std_flag
  clang -Wall -Werror -pedantic "$C_STD" ./src/*.c -o bush
else
  if [ -x "$(command -v gcc)" ]; then
    GCC_VERSION=$(gcc --version | grep gcc | awk '{split($3, ver, "."); print ver[1]}')
    set_std_flag
    gcc -Wall -Werror -pedantic "$C_STD" ./src/*.c -o bush
  else
    echo "clang and gcc compilers not found in your system. Please compile manually."
    exit "$EXIT_CODE"
  fi
fi

if [ -f bush ]; then
  echo "compilation successful."
else
  echo "something went wrong."
  exit "$EXIT_CODE"
fi
