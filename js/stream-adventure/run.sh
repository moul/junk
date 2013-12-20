#!/bin/sh

if [ -z $1 ]; then
    stream-adventure
    exit 0
fi

#set -x

export NODE_PATH=$NODE_PATH:$HOME/node_modules/

LEVEL=$(echo $1 | sed 's/\.coffee//;s/\.js//')

trap 'kill 0' SIGINT SIGTERM EXIT

stream-adventure select $LEVEL >/dev/null

TMPDIR=/tmp/stream-adventure-compile
mkdir -p $TMPDIR

CMD1="coffee -o $TMPDIR/ -c $LEVEL.coffee"
CMD2="clear; stream-adventure verify $TMPDIR/$LEVEL.js"

bash -c "$CMD1"
bash -c "$CMD2"

if [ "$2" = "watch" ]; then
    fswatch . "$CMD1" &
    fswatch $TMPDIR "$CMD2"
fi
