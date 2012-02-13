/**
 * libnetcli/net.c
 *
 * Copyright (c) Manfred Touron 2008
 */

#include <stdio.h>
#include <netdb.h>
#include <stddef.h>
#include <string.h>

#include "core.h"

int	lnc_init_connect(METHOD_ARGS)
{
  int	opt;

  if ((THIS->he = gethostbyname(THIS->hostname)) == NULL)
    return (0);
  THIS->pe = getprotobyname("tcp");
  THIS->sin.sin_family = AF_INET;
  THIS->sin.sin_port = htons(THIS->port);
  memcpy(&THIS->sin.sin_addr, THIS->he->h_addr_list[0], THIS->he->h_length);
  opt = 1;
  if ((THIS->fd = socket(PF_INET, SOCK_STREAM, THIS->pe->p_proto))
      == -1 || -1 ==
      setsockopt(THIS->fd, SOL_SOCKET, SO_REUSEADDR,
		 (void *)&opt, sizeof(opt)))
    return (0);
  return (1);
}

lnc	lnc_connect(char *hostname, int port)
{
  lnc	this;

  this = lnc_new();
  THIS->hostname = hostname;
  THIS->port = port;
  if (!lnc_init_connect(this) ||
      !(THIS->connected =
	(connect(THIS->fd, (struct sockaddr *)&THIS->sin,
		 sizeof(struct sockaddr_in)) != -1)))
    {
      perror("connect");
      METHOD(unset, (this));
      this = NULL;
    }
  return (this);
}
