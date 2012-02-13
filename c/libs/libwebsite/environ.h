/**
 * libwebsite/environ.h
 *
 * Copyright (c) Manfred Touron 2008
 */

#ifndef LIBWEBSITE_ENVIRON_H
# define LIBWEBSITE_ENVIRON_H

# include <stddef.h>

# include "libwebsite.h"

# define GETENV(NAME)	ws_get_environ(#NAME "=")

int	ws_print_environ(void);
char	*ws_get_environ(const char *);

#endif /* !LIBWEBSITE_ENVIRON_H */
