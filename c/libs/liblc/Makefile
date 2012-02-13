##
## liblc/Makefile
##
## Copyright (c) Manfred Touron 2008
##

.include "system.mk"

########################################

LIBRARY		+=	liblc

SOURCES		+=	core.c debug.c each.c lc.c lc_node.c push.c	\
			sort.c length.c shift.c unshift.c remove.c	\
			find.c

CFLAGS		+=	$(LIBMLUTIL_INC)
LDFLAGS		+=	$(LIBMLUTIL_LIB)
DEPENDS		+=	$(LIBMLUTIL_DEP)

TESTERS		+=	tester tester2

########################################

.include "rules.mk"

########################################

testers		:	$(TESTERS)

tester		:	$@.o liblc.a
			$(CC) $> -o $@ $(LDFLAGS)

tester2		:	$@.o liblc.a
			$(CC) $> -o $@ $(LDFLAGS)