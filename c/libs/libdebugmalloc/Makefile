CC			=	gcc
AR			=	ar
ARFLAGS			=	cr
RANLIB			=	ranlib
all			:	debugxmallocsimple.so debugxmalloc.so libdebugmalloc.a
libdebugmalloc.a	:	xmalloc.o
				$(AR) $(ARFLAGS) $@ xmalloc.o
				$(RANLIB) $@
debugxmalloc.so		:	debugxmallocsimple.so libxmalloc.o
				$(CC) libxmalloc.o -shared		\
				-nostartfiles -o $@
debugxmallocsimple.so	:	libxmallocsimple.o
				$(CC) $> -shared -nostartfiles -o $@
test			:	test.o xmalloc.o
				$(CC) -Wl,--export-dynamic -o $@ $>
clean			:
				rm -f *.o
fclean			:	clean
				rm -f debugxmalloc.so libdebugmalloc.a	\
				debugxmallocsimple.so test
re			:	fclean all
