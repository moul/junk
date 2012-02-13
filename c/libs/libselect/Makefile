##
## libselect/Makefile
##
## Copyright (c) Manfred Touron 2008
##

NAME		=	libselect.a

SRC		=	select.c core.c misc.c

OBJ		=	$(SRC:.c=.o)

#DEFINES	=	-DNVERBOSE
DEBUG		=	-ggdb

CFLAGS		=	-W -Wall -ansi -pedantic -std=c99 -I..
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
			$(CC) tester.o -o $@ -L. -lselect -L../liblc -llc

.c.o		:
			$(CC) $(CFLAGS) -c $? -o $@

clean		:
			$(RM) *~ $(OBJ) tester*.o *.core

fclean		:	clean
			$(RM) $(NAME) $(TESTERS)

re		:	fclean all

.PHONY		:	all clean fclean re testers
