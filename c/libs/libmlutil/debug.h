/**
 * libmlutil/debug.h
 *
 * Copyright (c) Manfred Touron 2008
 */

#ifndef LIBMLUTIL_DEBUG_H
# define LIBMLUTIL_DEBUG_H

# include <stdarg.h>

# define DCOL(NB)			(31 + (4 + (NB)) % 5)

# ifdef __DEBUG_ASCII
#  define D(X)				X
#  define DEBUG_ASCII(LINE, STR, ...)				\
  debug_ascii(__FILE__, __LINE__, (char *)__func__,		\
	      LINE, STR, __VA_ARGS__)
#  define DEBUG_ASCII_IN		DEBUG_ASCII(1, (char *)__func__, 0)
#  define DEBUG_ASCII_IN_SHORT		DEBUG_ASCII(0, (char *)__func__, 0)
#  define DEBUG_ASCII_OUT		DEBUG_ASCII(-1, (char *)__func__, 0)
#  define RETURN(ret)			{ DEBUG_ASCII_OUT; return (ret); }
#  define RETURN_VOID			{ DEBUG_ASCII_OUT; return ; }
# else /* __DEBUG_ASCII */
#  define D()
#  define DEBUG_ASCII(...)
#  define DEBUG_ASCII_IN
#  define DEBUG_ASCII_IN_SHORT
#  define DEBUG_ASCII_OUT
#  define RETURN(ret)			return (ret)
#  define RETURN_VOID			return
# endif /* !__DEBUG_ASCII */

void		debug_ascii_v(char *, int, char *, int, char *, va_list);
void		debug_ascii(char *, int, char *, int, char *, ...);
extern void	(*mlutil_status_fn)(const char *, va_list);
void		status(const char *, ...);
void		_status_fn_def(const char *, va_list);

#endif /* !LIBMLUTIL_DEBUG_H */
