#!/bin/sh

ROOT="$1"
DEST="$2"

# usage:
#   $0 ./autonomous-archive D501E5EB > archive.enc
#   $0 ./autonomous-archive D501E5EB | nc 10.42.42.42 3000

tar cf - "$ROOT" | gpg --encrypt -r "$DEST" -z 9
