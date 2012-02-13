##
## libmlutil/Makefile
##
## Copyright (c) Manfred Touron 2008
##

.include "system.mk"

########################################

LIBRARY		+=	libmlutil

SOURCES		+=	core.c debug.c misc.c output.c util.c string.c	\
			hash.c daemon.c xmalloc.c time.c rand.c

TESTERS		+=	tester

########################################

.include "rules.mk"

########################################

testers		:	$(TESTERS)

tester		:	tester.o libmlutil.a
			$(CC) $> -o $@ $(LDFLAGS)