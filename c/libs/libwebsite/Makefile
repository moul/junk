##
## libwebsite/Makefile
##
## Copyright (c) Manfred Touron 2008
##

.include "system.mk"

########################################

LIBRARY		+=	libwebsite

SOURCES		+=	core.c website.c header.c environ.c url.c

TESTERS		+=	tester

########################################

.include "rules.mk"

########################################

testers		:	$(TESTERS)

tester		:	tester.o libwebsite.a
			$(CC) $> -o $@ $(LDFLAGS)
