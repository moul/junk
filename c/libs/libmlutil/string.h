/**
 * libmlutil/string.h
 *
 * Copyright (c) Manfred Touron 2008
 */

#ifndef LIBMLUTIL_STRING_H
# define LIBMLUTIL_STRING_H

# include <string.h>

# include "common.h"
# include "types.h"

# define MAX_WORDS	1024

extern int	mu_strcmp(void *, void *);
extern char	*addslashes(char *);
extern char	**strtowordtab(char *, char, char);
extern int	wordtablength(char **);
extern int	vprintflen(char *, va_list);
extern int	printflen(char *, ...);

#endif /* !LIBMLUTIL_MISC_H */
