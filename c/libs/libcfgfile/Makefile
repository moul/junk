##
## libcfgfile/Makefile
##
## Copyright (c) Manfred Touron 2008
##

.include "system.mk"

########################################

LIBRARY		+=	libcfgfile

SOURCES		+=	cfgfile.c core.c misc.c parse.c

TESTERS		+=	tester

DEPENDS		+=	$(TOPDIR)/liblc/liblc.a

CFLAGS		+=	$(LIBLC_INC) $(LIBRBUF_INC)
LDFLAGS		+=	$(LIBLC_LIB) $(LIBRBUF_LIB)
DEPENDS		+=	$(LIBLC_DEP) $(LIBRBUF_DEP)

.ifdef DBG_LCFL && $(DBG_LCFL) == 1
DEBUG		+=	-D__DEBUG_LIBCFGFILE
.endif

########################################

.include "rules.mk"

########################################

testers		:	$(TESTERS)

tester		:	tester.o libcfgfile.a
			$(CC) $> -o $@ $(LDFLAGS)