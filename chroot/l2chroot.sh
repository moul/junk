#!/bin/sh

DEST="$1"
BIN="$2"

FILES=$(ldd "$BIN" | sed '/\//!d;s/^[^\/]*\(\/.*\)\ .*/\1/g')

for file in $FILES; do
    d=$(dirname "$file")
    mkdir -p "$DEST/$d"
    cp "$file" "$DEST/$d"
done

d=$(dirname "$BIN")
mkdir -p "$DEST/$d"
cp "$BIN" "$DEST/$d"

