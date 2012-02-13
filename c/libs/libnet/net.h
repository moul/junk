/**
 * libnet/net.h
 *
 * Copyright (c) Manfred Touron 2008
 */

#ifndef LIBNET_NET_H
# define LIBNET_NET_H

# include <stdarg.h>
# include <sys/socket.h>
# include <sys/types.h>
# include <netinet/in.h>

# include <librbuf/rbuf.h>

# include "common.h"

int	libnet_close(int);
int	libnet_write(int, char *, int);
int	libnet_read(int, char *, int);
int	libnet_sendudp(int, struct sockaddr_in *, char *);
int	libnet_printfudp(int, struct sockaddr_in *,
			 const char *, ...);
int	libnet_vprintfudp(int, struct sockaddr_in *,
			  const char *, va_list);
int	libnet_send(int, char *);
int	libnet_printf(int, const char *, ...);
int	libnet_vprintf(int, const char *, va_list);
int	libnet_sendline(int, char *);
int	libnet_rbufread(int, rbuf);
rbuf	libnet_rbufget(int);

#endif /* !LIBNET_NET_H */
