/**
 * libnet/server.c
 *
 * Copyright (c) Manfred Touron 2008
 */

#include <stdio.h>
#include <netdb.h>
#include <stddef.h>
#include <string.h>
#include <arpa/inet.h>
#include <errno.h>
#include <fcntl.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/filio.h>
#include <sys/ioctl.h>
#include <sys/select.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sysexits.h>
#include <unistd.h>

#include <libmlutil/xmalloc.h>

#include "core.h"
#include "server.h"

char			*_libnet_accept_hostname = NULL;

int			libnet_create_tcp_server(int port)
{
  struct sockaddr_in	sock;
  int			fd;
  int			opt;
  struct protoent	*pe;

  DEBUG_ASCII_IN;
  if (!port)
    RETURN (-1);
  pe = getprotobyname("tcp");
  if ((fd = socket(AF_INET, SOCK_STREAM, pe->p_proto)) < 0)
    {
      perror("tcp socket");
      RETURN (-1);
    }
  opt = 1;
  if (setsockopt(fd, SOL_SOCKET, SO_REUSEADDR,
		 (void *)&opt, sizeof(opt)) < 0)
    {
      perror("setsockopt");
      RETURN (-1);
    }
  sock.sin_family = AF_INET;
  sock.sin_addr.s_addr = INADDR_ANY;
  sock.sin_port = htons(port);
  if (bind(fd, (struct sockaddr *)&sock, sizeof(struct sockaddr_in)) < 0)
    {
      shutdown(fd, 2);
      close(fd);
      perror("bind");
      RETURN (-1);
    }
  if (listen(fd, 42) < 0)
    {
      shutdown(fd, 2);
      close(fd);
      perror("listen");
      RETURN (-1);
    }
  RETURN (fd);
}

int			_libnet_create_udp_server_in(lnet_udp *udp,
						     int port, char *ip)
{
  struct ip_mreq	imreq;

  DEBUG_ASCII_IN;
  if ((udp->fd_in = socket(PF_INET, SOCK_DGRAM, IPPROTO_IP)) < 0)
    {
      perror("udp socket");
      RETURN (-1);
    }
  udp->saddr_in.sin_family = PF_INET;
  udp->saddr_in.sin_addr.s_addr = htonl(INADDR_ANY);
  udp->saddr_in.sin_port = htons(port);
  if (bind(udp->fd_in, (struct sockaddr *)&udp->saddr_in,
	   sizeof(struct sockaddr_in)) < 0)
    {
      shutdown(udp->fd_in, 2);
      close(udp->fd_in);
      perror("bind");
      RETURN (-1);
    }
  imreq.imr_multiaddr.s_addr = inet_addr(ip);
  imreq.imr_interface.s_addr = INADDR_ANY;
  if (setsockopt(udp->fd_in, IPPROTO_IP, IP_ADD_MEMBERSHIP,
		 (void *)&imreq, sizeof(struct ip_mreq)) < 0)
    {
      perror("setsockopt");
      RETURN (-1);
    }
  RETURN (1);
}

int	_libnet_create_udp_server_out(lnet_udp *udp, int port, char *ip)
{
  int	opt;
  int	ttl;

  DEBUG_ASCII_IN;
  if ((udp->fd_out = socket(PF_INET, SOCK_DGRAM, IPPROTO_IP)) < 0)
    {
      perror("udp socket");
      RETURN (-1);
    }
  udp->saddr_out.sin_family = PF_INET;
  udp->saddr_out.sin_port = htons(0);
  udp->saddr_out.sin_addr.s_addr = htonl(INADDR_ANY);
  if (bind(udp->fd_out, (struct sockaddr *)&udp->saddr_out,
	   sizeof(struct sockaddr_in)) < 0)
    {
      shutdown(udp->fd_out, 2);
      close(udp->fd_out);
      perror("bind");
      RETURN (-1);
    }
  udp->iaddr_out.s_addr = INADDR_ANY;
  ttl = 2;
  opt = 0;
  if (setsockopt(udp->fd_out, IPPROTO_IP, IP_MULTICAST_IF, &udp->iaddr_out,
		 sizeof(struct in_addr)) < 0 ||
      setsockopt(udp->fd_out, IPPROTO_IP, IP_MULTICAST_TTL, &ttl,
		 sizeof(int)) < 0 ||
      setsockopt(udp->fd_out, IPPROTO_IP, IP_MULTICAST_LOOP, &opt,
		 sizeof(int)) < 0)
    {
      perror("setsockopt");
      RETURN (-1);
    }
  udp->saddr_out.sin_family = PF_INET;
  udp->saddr_out.sin_port = htons(port);
  udp->saddr_out.sin_addr.s_addr = inet_addr(ip);
  RETURN (1);
}

lnet_udp	*libnet_create_udp_server(int port, char *ip)
{
  lnet_udp	*udp;

  DEBUG_ASCII_IN;
  if (!port)
    RETURN (NULL);
  udp = ALLOC(lnet_udp);
  if (_libnet_create_udp_server_in(udp, port, ip) < 0 ||
      _libnet_create_udp_server_out(udp, port, ip) < 0)
    {
      free(udp);
      RETURN (NULL);
    }
  RETURN (udp);
}

char	*libnet_accept_gethostname(void)
{
  DEBUG_ASCII_IN;
  RETURN (_libnet_accept_hostname);
}

int			libnet_accept(int fd)
{
  struct sockaddr_in	in;
  int			ret;
  int			size;

  DEBUG_ASCII_IN;
  size = sizeof(in);
  _libnet_accept_hostname = NULL;
  if ((ret = accept(fd, (struct sockaddr *)&in,
		   (socklen_t *)&size)) < 0)
    {
      perror("accept");
      RETURN (-1);
    }
  _libnet_accept_hostname = inet_ntoa(in.sin_addr);
  RETURN (ret);
}
