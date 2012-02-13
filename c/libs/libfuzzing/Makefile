##
## libfuzzing/Makefile
##
## Copyright (c) Manfred Touron 2008
##

.include "system.mk"

########################################

LIBRARY		=	libfuzzing

SOURCES		+=	fuzzing.c core.c

TESTERS		+=	tester

CFLAGS		+=	
LDFLAGS		+=	
DEPENDS		+=	

.ifdef DBG_LFUZZING && $(DBG_LFUZZING) == 1
DEBUG		+=	-D__DEBUG_LIBFUZZING
.endif

########################################

.include "rules.mk"

########################################

testers		:	$(TESTERS)

tester		:	$@.o $(LIBRARY).a
			$(CC) $> -o $@ $(LDFLAGS)
