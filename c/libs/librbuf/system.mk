##
## system.mk
##
## Copyright (c) Manfred Touron 2008
##

.if exists(../.project)
TOPDIR		=	..
.include "$(TOPDIR)/build/system-inc.mk"
.else

DEBUG		=	-ggdb

CFLAGS		=	-W -Wall -ansi -std=c99

RM		=	rm -f
CC		=	gcc
AR		=	ar
ARFLAGS		=	cr
RANLIB		=	ranlib

.endif
