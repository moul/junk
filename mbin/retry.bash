#!/bin/bash

while true; do
    eval "$@"
    if [ $? == 0 ]; then
        exit
    fi
    sleep .5
done
