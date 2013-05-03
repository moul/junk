#!/bin/sh

addr=$(printf "0%x0042#\n" $((0xA42+$RANDOM)))

echo $addr
