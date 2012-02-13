##
## libnetcli/Makefile
##
## Copyright (c) Manfred Touron 2008
##

.include "system.mk"

########################################

LIBRARY		+=	libnetcli

SOURCES		+=	net.c core.c lnc.c method.c select.c misc.c	\
			select_type.c select_link.c

TESTERS		+=	tester tester2

CFLAGS		+=	$(LIBLC_INC) $(LIBRBUF_INC) $(LIBMLUTIL_INC)
LDFLAGS		+=	$(LIBLC_LIB) $(LIBRBUF_LIB) $(LIBMLUTIL_LIB)
DEPENDS		+=	$(LIBLC_DEP) $(LIBRBUF_DEP) $(LIBMLUTIL_DEP)

########################################

.include "rules.mk"

########################################

testers		:	$(TESTERS)

tester		:	tester.o libnetcli.a
			$(CC) $> -o $@ $(LDFLAGS)

tester2		:	tester2.o libnetcli.a
			$(CC) $> -o $@ $(LDFLAGS)
