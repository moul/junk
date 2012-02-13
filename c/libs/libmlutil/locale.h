/**
 * libmlutil/locale.h
 *
 * Copyright (c) Manfred Touron 2008
 */

#ifndef LIBMLUTIL_LOCALE_H
# define LIBMLUTIL_LOCALE_H

# ifdef CF_GETTEXT
#  define TR(X)		gettext(X)
#  define DUMMY_TR(X)	X
# else /* CF_GETTEXT */
#  define TR(X)		X
#  define DUMMY_TR(X)	X
# endif /* !CF_GETTEXT */

#endif /* !LIBMLUTIL_LOCALE_H */
