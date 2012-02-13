/**
 * libnet/client.c
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

#include "core.h"
#include "net.h"

char			*_libnet_connect_hostname = NULL;

char			*libnet_connect_hostname(void)
{
  return (_libnet_connect_hostname);
}

int			libnet_connect(const char *hostname, int port)
{
  int			fd;
  int			opt;
  struct hostent	*he;
  struct sockaddr_in    sin;
  struct protoent       *pe;

  DEBUG_ASCII_IN;
  if ((he = gethostbyname(hostname)) == NULL)
    {
      perror("gethostbyname");
      RETURN (-1);
    }
  pe = getprotobyname("tcp");
  sin.sin_family = AF_INET;
  sin.sin_port = htons(port);
  memcpy(&sin.sin_addr, he->h_addr_list[0], he->h_length);
  _libnet_connect_hostname = inet_ntoa(sin.sin_addr);
  opt = 1;
  if ((fd = socket(PF_INET, SOCK_STREAM, pe->p_proto)) < 0)
    {
      perror("socket");
      RETURN (-1);
    }
  if (setsockopt(fd, SOL_SOCKET, SO_REUSEADDR,
		 (void *)&opt, sizeof(opt)) < 0)
    {
      perror("setsockopt");
      RETURN (-1);
    }
  if (connect(fd, (struct sockaddr *)&sin, sizeof(struct sockaddr_in))
      < 0)
    {
      perror("connect");
      RETURN (-1);
    }
  RETURN (fd);
}
