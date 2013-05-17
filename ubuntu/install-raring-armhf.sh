#!/bin/sh

DEST=/mnt

apt-get install debootstrap

debootstrap --variant=minbase --foreign --arch armhf raring $DEST

chroot $DEST /bin/bash
/debootstrap/debootstrap --second-stage

echo "deb http://ports.ubuntu.com raring main restricted universe
deb-src http://ports.ubuntu.com raring main restricted universe" > /etc/apt/sources.list

apt-get update
apt-get install apt-utils openssh-server htop tmux emacs24-nox wget less
