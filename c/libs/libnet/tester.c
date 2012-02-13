/**
 * libnetcli/tester.c
 *
 * Copyright (c) Manfred Touron 2008
 */

#include <stdio.h>
#include <stdlib.h>

#include <libmlutil/debug.h>

#include "server.h"
#include "select.h"

#define BUF_SIZE	1024

void	usage(char *);

int	main(int ac, char **av)
{
  int	fd_listen;
  int	fd_client;
  int	ret;
  char	line[BUF_SIZE];

  DEBUG_ASCII_IN;
  if (ac < 2)
    usage(av[0]);
  printf ("[+] New tcp server on port %d\n", atoi(av[1]));
  if ((fd_listen = libnet_create_tcp_server(atoi(av[1]))) < 0)
    {
      printf("[-] Error\n");
      RETURN (-1);
    }
  printf("[+] Server is listening...\n");
  libnet_select_reset();
  libnet_select_add_fd(fd_listen);
  libnet_select_settimeout(0, 0);
  fd_client = -1;
  while (42)
    {
      if ((ret = libnet_select()))
	{
	  if (libnet_select_isset(fd_client))
	    {
	      if (!libnet_read(fd_client, line, BUF_SIZE))
		libnet_close(fd_client);
	      else
		printf("read: %s\n", line);
	    }
	  if (libnet_select_isset(fd_listen))
	    {
	      printf("[+] New client\n");
	      fd_client = libnet_accept(fd_listen);
	      libnet_select_add_fd(fd_client);
	    }
	  printf("[+] libnet_select = %d\n", ret);
	}
    }
  RETURN (0);
}

void	usage(char *moul)
{
  printf("usage: %s PORT\n", moul);
  exit(-1);
}
