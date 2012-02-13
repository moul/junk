##
## libgetopt/Makefile
##
## Copyright (c) Manfred Touron 2008
##

.include "system.mk"

########################################

LIBRARY		+=	libgetopt

SOURCES		+=	getopt.c core.c

TESTERS		+=	tester

########################################

.include "rules.mk"

########################################

testers		:	$(TESTERS)

tester		:	tester.o libgetopt.a
			$(CC) $> -o $@ $(LDFLAGS)
