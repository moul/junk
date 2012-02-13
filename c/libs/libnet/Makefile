##
## libnet/Makefile
##
## Copyright (c) Manfred Touron 2008
##

.include "system.mk"

########################################

LIBRARY		+=	libnet

SOURCES		+=	core.c net.c select.c server.c client.c

TESTERS		+=	tester tester2 tester3

CFLAGS		+=	$(LIBLC_INC) $(LIBRBUF_INC) $(LIBMLUTIL_INC)
LDFLAGS		+=	$(LIBLC_LIB) $(LIBRBUF_LIB) $(LIBMLUTIL_LIB)
DEPENDS		+=	$(LIBLC_DEP) $(LIBRBUF_DEP) $(LIBMLUTIL_DEP)

.ifdef DBG_LNET && $(DBG_LNET) == 1
DEBUG		+=	-D__DEBUG_LIBNET
.endif

########################################

.include "rules.mk"

########################################

testers		:	$(TESTERS)

tester		:	$@.o libnet.a
			$(CC) $> -o $@ $(LDFLAGS)

tester2		:	$@.o libnet.a
			$(CC) $> -o $@ $(LDFLAGS)

tester3		:	$@.o libnet.a
			$(CC) $> -o $@ $(LDFLAGS)
