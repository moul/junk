#!/bin/sh
TESTER=tester
#DEBUG=/home/moul/rendu/tek/2/libdebugmalloc/debugxmallocsimple.so
clear
make re &&							\
make $TESTER &&	echo &&						\
LD_PRELOAD=$DEBUG ./$TESTER $@ && printf "\nOK\n\n" ||		\
printf "\nKO\n\n"