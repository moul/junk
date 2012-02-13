##
## libserv/Makefile
##
## Copyright (c) Manfred Touron 2008
##

NAME		=	libserv.a

SRC		=	xmalloc.c client.c net.c parser.c buffer.c	\
			timer.c api.c routine.c misc.c select.c

OBJ		=	$(SRC:.c=.o)

#DEFINES	=	-DNVERBOSE
DEBUG		=	-ggdb

CFLAGS		=	-W -Wall -ansi -pedantic -std=c99
CFLAGS		+=	$(DEBUG)
CFLAGS		+=	$(DEFINES   )

RM		=	rm -f
CC		=	gcc
AR		=	ar
ARFLAGS		=	cr
RANLIB		=	ranlib

TESTERS		=	tester

$(NAME)		:	$(OBJ)
			$(AR) $(ARFLAGS) $@ $(OBJ)
			$(RANLIB) $@

all		:	$(NAME)

testers		:	$(TESTERS)

tester		:	tester.o $(NAME)
			$(CC) $< -o $@ -L. -lserv

.c.o		:
			$(CC) $(CFLAGS) -c $? -o $@

clean		:
			$(RM) *~ $(OBJ)

fclean		:	clean
			$(RM) $(NAME) $(TESTERS)

re		:	fclean all

.PHONY		:	all clean fclean re testers
