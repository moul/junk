/**
 * libserialize/libserialize.h
 *
 * Copyright (c) Manfred Touron 2008
 */

#ifndef LIBSERIALIZE_CORE_H
# define LIBSERIALIZE_CORE_H

# include <stddef.h>

# include "libserialize.h"

# define ALLOC(X)		malloc(sizeof(X))
# define ALLOC_N(X, N)		malloc(sizeof(X) * N)

int	serialize_init(void);
int	serialize_name_cmpfn(void *, void *);
void	serialize_parse_struct(srlz *);

#endif /* !LIBSERIALIZE_CORE_H */
