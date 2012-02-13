/**
 * libmlutil/misc.h
 *
 * Copyright (c) Manfred Touron 2008
 */

#ifndef LIBMLUTIL_MISC_H
# define LIBMLUTIL_MISC_H

# include <stdlib.h>
# include <stdio.h>
# include <assert.h>
# include "types.h"
# include "xmalloc.h"

# define XOR(X, Y)	(((X) == 0) != ((Y) == 0))

extern char	*scopy(const char *);
extern char	*scopyn(const char *, size_t);
extern char	*scat(const char *, const char *);
extern char	*scatn(const char *, ssize_t, const char *, ssize_t);
extern char	*scat3(const char *, const char *, const char *);
extern void	stripws(char *);

extern const char	*simple_basename(const char *);

extern bool	readf(FILE *, void *, size_t);
extern bool	writef(FILE *, const void *, size_t);

#endif /* !LIBMLUTIL_MISC_H */
