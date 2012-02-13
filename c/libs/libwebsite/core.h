/**
 * libwebsite/core.h
 *
 * Copyright (c) Manfred Touron 2008
 */

#ifndef LIBWEBSITE_CORE_H
# define LIBWEBSITE_CORE_H

# include <stddef.h>

# include "libwebsite.h"

# define ALLOC(X)		malloc(sizeof(X))
# define ALLOC_N(X, N)		malloc(sizeof(X) * N)

#endif /* !LIBWEBSITE_CORE_H */
