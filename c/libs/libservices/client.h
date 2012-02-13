/**
 * libservices/client.h
 *
 * Copyright (c) Manfred Touron 2008
 */

#ifndef LIBSERVICES_CLIENT_H
# define LIBSERVICES_CLIENT_H

# include <libmlutil/valist.h>

# include "common.h"

# define SERVICE_CALL(NAME, ...)	service_call(NAME,		\
						     VARGS(__VA_ARGS__))

extern int	service_exists(const char *);
extern char	*service_call(const char *, VARGS_T);
extern void	services_list(void);
int		service_exists(const char *);

#endif /* !LIBSERVICES_CLIENT_H */
