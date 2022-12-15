#!/bin/bash

# Run from this directory.
cd "${0%/*}" || exit 1

# Default versions to help set default standards.
CLANG_VERSION=4
GCC_VERSION=3

# Function to set standard compilation flag.
set_std_flag() {
  if [ "$CLANG_VERSION" -ge 10 ] || [ "$GCC_VERSION" -ge 10 ]; then
    C_STD="-std=gnu2x"
  elif [ "$CLANG_VERSION" -ge 8 ] || [ "$GCC_VERSION" -ge 7 ]; then
    C_STD="-std=gnu17"
  elif [ "$CLANG_VERSION" -ge 5 ] || [ "$GCC_VERSION" -ge 4 ]; then
    C_STD="-std=gnu11"
  else
    # Default standard.
    C_STD="-std=gnu99"
  fi
}

# Exit code to help the install.sh script determine if the compilation was successful.
EXIT_CODE=13

# Fresh compilation, remove previously compiled executable.
if [ -f bush ]; then
  rm bush
fi

# Prioritize Clang if it exists in the system.
if [ -x "$(command -v clang)" ]; then
  CLANG_VERSION=$(clang --version | grep -n 1 | awk '{split($4, ver, "."); print ver[1]}')
  set_std_flag
  clang -Wall -Werror -pedantic "$C_STD" ./src/*.c -o bush
  echo "Compiled with Clang $CLANG_VERSION with C standard $C_STD"
else
  # Compile with GCC if Clang is not found.
  if [ -x "$(command -v gcc)" ]; then
    GCC_VERSION=$(gcc --version | grep gcc | awk '{split($3, ver, "."); print ver[1]}')
    set_std_flag
    gcc -Wall -Werror -pedantic "$C_STD" ./src/*.c -o bush
    echo -e "Compiled with GCC $GCC_VERSION with C standard $C_STD"
  else
    # Both Clang and GCC are not present in the system.
    echo "clang and gcc compilers not found in your system. Please compile manually."
    exit "$EXIT_CODE"
  fi
fi

# Report the outcome of compilation.
if [ -f bush ]; then
  echo "Compilation successful."
else
  echo "Something went wrong, compilation failed."
  exit "$EXIT_CODE"
fi
