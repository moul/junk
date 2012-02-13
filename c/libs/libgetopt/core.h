/**
 * libgetopt/libgetopt.h
 *
 * Copyright (c) Manfred Touron 2008
 */

#ifndef LIBGETOPT_CORE_H
# define LIBGETOPT_CORE_H

# include <stddef.h>

# include "libgetopt.h"

# define ALLOC(X)		malloc(sizeof(X))
# define ALLOC_N(X, N)		malloc(sizeof(X) * N)

#endif /* !LIBGETOPT_CORE_H */
