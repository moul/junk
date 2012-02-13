#!/bin/sh
TESTER=tester2
#DEBUG=/home/moul/rendu/tek/2/libdebugmalloc/debugxmallocsimple.so
clear
make re &&								\
make $TESTER &&	echo &&							\
LD_PRELOAD=$DEBUG ./$TESTER localhost 4243 && printf "\nOK\n\n" ||	\
printf "\nKO\n\n"