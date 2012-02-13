##
## libevent/Makefile
##
## Copyright (c) Manfred Touron 2008
##

.include "system.mk"

########################################

LIBRARY		+=	libevent

SOURCES		+=	add.c call.c core.c debug.c del.c event.c	\
			find.c get.c events.c module.c

TESTERS		+=	tester

DEPENDS		+=	$(TOPDIR)/liblc/liblc.a

CFLAGS		+=	$(LIBLC_INC)
LDFLAGS		+=	$(LIBLC_LIB)
DEPENDS		+=	$(LIBLC_DEP)

########################################

.include "rules.mk"

########################################

testers		:	$(TESTERS)

tester		:	tester.o libevent.a
			$(CC) $> -o $@ $(LDFLAGS)
