#!/bin/bash

DEST="$1"
shift
BINS=$@

LIBS=/liblibgcc_s* /lib/ld-linux*.so* 2>/dev/null
CONFIGFILES=/etc/localtime /etc/resolv.conf /etc/nsswitch.conf

##################

rm -rf "$DEST"
mkdir -p "$DEST"/{tmp,proc,dev,www,bin,usr/bin,lib}

for file in $BINS $LIBS; do
    ./l2chroot.sh "$DEST" "$file" 2>/dev/null
done

for file in $CONFIGFILES; do
    cat $file > $DEST/$file
done
