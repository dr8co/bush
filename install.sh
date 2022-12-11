#!/bin/bash

if [ "$(id -u)" != "0" ]; then
  echo "Sorry, you are not root."
  exit 1
fi

BUSH="bush"
MAN="man/burning-bush.1"
EXIT_CODE=13

APP_PATH="/opt/burning_bush"
BIN_PATH="/usr/local/bin"
MAN_PATH="/usr/local/share/man/man1"

echo -e "Installing The Burning Bush.."

echo -e "Compiling..\n"

./compile.sh

CODE=$?

if [ $CODE == $EXIT_CODE ]; then
  echo -e "Compilation Failed. Please resolve the issue and try again."
  exit 1
fi

echo -e "Installing binaries..\n"

if [ ! -d "$APP_PATH" ]; then
  mkdir -p "$APP_PATH"
fi

cp "$BUSH" "$APP_PATH/$BUSH"

chmod +x "$APP_PATH/$BUSH"

ln -s "$APP_PATH/$BUSH" "$BIN_PATH/$BUSH"

echo -e "Installing man pages..\n"

if [ ! -d "$MAN_PATH" ]; then
  mkdir -p "$MAN_PATH"
fi

install -g 0 -o 0 -m 0644 "$MAN" "$MAN_PATH"

gzip "$MAN_PATH/burning-bush.1"

echo -e "Updating man database..\n"

mandb > /dev/null 2>&1

echo "All set."
