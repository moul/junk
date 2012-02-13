##
## librbuf/Makefile
##
## Copyright (c) Manfred Touron 2008
##

.include "system.mk"

########################################

LIBRARY		+=	librbuf

SOURCES		+=	rbuf.c core.c

TESTERS		+=	tester tester2

########################################

.include "rules.mk"

########################################

testers		:	$(TESTERS)

tester		:	$@.o librbuf.a
			$(CC) $> -o $@ $(LDFLAGS)

tester2		:	$@.o librbuf.a
			$(CC) $> -o $@ $(LDFLAGS)