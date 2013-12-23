#!/bin/sh

export NODE_PATH=$NODE_PATH:$HOME/node_modules/

if [ -z $1 ]; then
    stream-adventure
    exit 0
fi

if [ "$1" = "all" ]; then
    for level in *.coffee; do
        $0 "$level"
    done
    exit 0
fi

#set -x

FULL=$(echo $1 | sed 's/\.coffee//;s/\.js//')
LEVEL=$(echo "$FULL" | cut -d'.' -f1)

LEVEL_UPPER=$(echo "$LEVEL" | sed 's/_/ /g;y/abcdefghijklmnopqrstuvwxyz/ABCDEFGHIJKLMNOPQRSTUVWXYZ/')
echo $LEVEL_UPPER

stream-adventure select "$LEVEL_UPPER" >/dev/null

TMPDIR=/tmp/stream-adventure-compile
mkdir -p $TMPDIR

CMD1="coffee -o $TMPDIR/ -c $FULL.coffee"
CMD2="clear; stream-adventure verify $TMPDIR/$FULL.js"

bash -c "$CMD1"
bash -c "$CMD2"

if [ "$2" = "watch" ]; then
    trap 'kill 0' SIGINT SIGTERM EXIT
    fswatch . "$CMD1" &
    fswatch $TMPDIR "$CMD2"
fi
