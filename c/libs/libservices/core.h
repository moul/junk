/**
 * libservices/libservice.h
 *
 * Copyright (c) Manfred Touron 2008
 */

#ifndef LIBSERVICES_CORE_H
# define LIBSERVICES_CORE_H

# include <stddef.h>

# include "libservices.h"
# include "module.h"
# include "client.h"

# define ALLOC(X)		malloc(sizeof(X))
# define ALLOC_N(X, N)		malloc(sizeof(X) * N)

void	services_init(void);
svc	service_find(const char *);
int	services_cmpfn(void *, void *);

#endif /* !LIBSERVICES_CORE_H */
