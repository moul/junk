##
## rules.mk
##
## Copyright (c) Manfred Touron 2008
##

.if exists($(TOPDIR)/build/rules.mk)
.include "$(TOPDIR)/build/rules.mk"
.else

CFLAGS		+=	$(DEBUG)
CFLAGS		+=	$(DEFINES)

OBJS		=	$(SRC:.c=.o)

all		:	$(TARGETS)

.c.o		:
			$(CC) $(CFLAGS) -c $? -o $@

clean		:
			$(RM) *~ $(OBJS) tester*.o *.core

fclean		:	clean
			$(RM) $(TARGETS) $(TESTERS)

re		:	fclean all

.PHONY		:	all clean fclean re testers

.endif
