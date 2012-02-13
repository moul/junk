##
## libservices/Makefile
##
## Copyright (c) Manfred Touron 2008
##

.include "system.mk"

########################################

LIBRARY		+=	libservices

SOURCES		+=	add.c services.c call.c misc.c

TESTERS		+=	tester

DEPENDS		+=	$(TOPDIR)/liblc/liblc.a

CFLAGS		+=	$(LIBLC_INC)
LDFLAGS		+=	$(LIBLC_LIB)
DEPENDS		+=	$(LIBLC_DEP)

########################################

.include "rules.mk"

########################################

testers		:	$(TESTERS)

tester		:	tester.o libservices.a
			$(CC) $> -o $@ $(LDFLAGS)
