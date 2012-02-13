/**
 * libnet/client.h
 *
 * Copyright (c) Manfred Touron 2008
 */

#ifndef LIBNET_CLIENT_H
# define LIBNET_CLIENT_H

# include <librbuf/rbuf.h>

# include "common.h"
# include "net.h"

extern char	*_libnet_connect_hostname;

int	libnet_connect(const char *, int);
char	*libnet_connect_hostname(void);

#endif /* !LIBNET_CLIENT_H */
