##
## libserialize/Makefile
##
## Copyright (c) Manfred Touron 2008
##

.include "system.mk"

########################################

LIBRARY		+=	libserialize

SOURCES		+=	serialize.c core.c add.c dump.c misc.c		\
			serialize_do.c

TESTERS		+=	tester

CFLAGS		+=	$(LIBLC_INC)
LDFLAGS		+=	$(LIBLC_LIB)
DEPENDS		+=	$(LIBLC_DEP)

########################################

.include "rules.mk"

########################################

testers		:	$(TESTERS)

tester		:	tester.o libserialize.a
			$(CC) $> -o $@ $(LDFLAGS)
