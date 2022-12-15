#!/bin/bash

# Run from this directory.
cd "${0%/*}" || exit 1

# sudo powers required.
if [ "$(id -u)" != "0" ]; then
  echo "Sorry, you are not root."
  exit 1
fi

BUSH="bush"

APP_PATH="/opt/burning_bush"
BIN_PATH="/usr/local/bin"
MAN_PATH="/usr/local/share/man/man1"

echo -e "Uninstalling The Burning Bush..\n"

echo "Cleaning man page.."
if [ -f "$MAN_PATH/burning-bush.1" ]; then
  rm -f "$MAN_PATH/burning-bush.1"
fi

if [ -f "$MAN_PATH/burning-bush.1.gz" ]; then
  rm -f "$MAN_PATH/burning-bush.1.gz"
fi

echo "Cleaning installed bush binary.."
if [ -f "$BIN_PATH/$BUSH" ]; then
  rm -f "$BIN_PATH/$BUSH"
fi

if [ -d "$APP_PATH" ]; then
  rm -rf "$APP_PATH"
fi

echo "Cleaning compiled binary.."
if [ -f "$BUSH" ]; then
  rm -f "$BUSH"
fi

echo -e "Updating man database..\n"

mandb > /dev/null 2>&1

echo "Successfully uninstalled The Burning Bush. Thank you, Bye! |(•◡•)|."
