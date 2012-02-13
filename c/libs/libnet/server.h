/**
 * libnet/server.h
 *
 * Copyright (c) Manfred Touron 2008
 */

#ifndef LIBNET_SERVER_H
# define LIBNET_SERVER_H

# include <librbuf/rbuf.h>

# include "common.h"
# include "net.h"

typedef struct
{
  int			fd_in;
  struct sockaddr_in	saddr_in;
  int			fd_out;
  struct sockaddr_in	saddr_out;
  struct in_addr	iaddr_out;
}			lnet_udp;

extern int	libnet_create_tcp_server(int);
extern lnet_udp	*libnet_create_udp_server(int, char *);
extern int	libnet_accept(int);
extern char	*libnet_accept_gethostname(void);

#endif /* !LIBNET_SERVER_H */
