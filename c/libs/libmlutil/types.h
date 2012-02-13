/**
 * libmlutil/types.h
 *
 * Copyright (c) Manfred Touron 2008
 */

#ifndef LIBMLUTIL_TYPES_H
# define LIBMLUTIL_TYPES_H

# include <sys/types.h>

typedef int			bool;
# define TRUE			((bool)1)
# define FALSE			((bool)0)

# ifndef NULL
#  define NULL			((void*)0)
# endif

# ifndef LIBMLUTIL_TYPEDEF_UXXX

#  ifndef uchar
#   define uchar		unsigned char
#  endif

#  ifndef ushort
#   define ushort		unsigned short
#  endif

#  ifndef uint
#   define uint			unsigned int
#  endif

#  ifndef ulong
#   define ulong		unsigned long
#  endif

# else /* LIBMLUTIL_TYPEDEF_UXXX */

#  ifndef uchar
typedef unsigned char		uchar
#  endif

#  ifndef ushort
typedef unsigned short		ushort
#  endif

#  ifndef uint
typedef unsigned int		uint
#  endif

#  ifndef ulong
typedef unsigned long		ulong
#  endif

# endif /* !LIBMLUTIL_TYPEDEF_UXXX */

#endif /* !LIBMLUTIL_TYPES_H */
