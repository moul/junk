/**
 * liblc/liblc.h
 *
 * Copyright (c) Manfred Touron 2008
 */

#ifndef LIBLC_CORE_H
# define LIBLC_CORE_H

# include <stddef.h>

# include "liblc.h"

# include <libmlutil/misc.h>

/*
# define ALLOC(X)		malloc(sizeof(X))
# define ALLOC_N(X, N)		malloc(sizeof(X) * N)
*/
typedef int			cmpfn(void *, void *);

lc_node	lc_node_new(void *, lc_node, lc_node);

#endif /* !LIBLC_CORE_H */
