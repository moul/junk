#!/bin/sh

ROOT="$1"


# usage:
#   cat archive.enc | $0 ./dest
#   nc -l -p 3000   | $0 ./dest

cat | gpg decrypt | tar xf "$ROOT"