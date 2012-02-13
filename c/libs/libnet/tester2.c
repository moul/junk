/**
 * libnetcli/tester2.c
 *
 * Copyright (c) Manfred Touron 2008
 */

#include <stdio.h>
#include <stdlib.h>

#include <librbuf/rbuf.h>
#include <libmlutil/debug.h>

#include "net.h"

#define BUF_SIZE	1024

void	usage(char *);

int	main(int ac, char **av)
{
  rbuf	buf;
  int	fd;
  char	*line;

  DEBUG_ASCII_IN;
  if (ac < 3)
    usage(av[0]);
  printf ("[+] Connecting to %s:%d\n", atoi(av[1]));
  if ((fd = libnet_connect(av[1], atoi(av[2]))) < 0)
    {
      printf("[-] Error\n");
      RETURN (-1);
    }
  printf("[+] Writing \"tota\\n\", 5\n");
  libnet_write(fd, "tota\n", 5);
  printf("[+] Sending \"toti\\ntotan\\n\"\n");
  libnet_send(fd, "toti\ntotan\n");
  printf("[+] Sending line \"totu\\nbla\\n\"\n");
  libnet_sendline(fd, "totu\nbla\n");
  printf("[+] Rbuf get\n");
  buf = libnet_rbufget(fd);
  while (line = rbuf_get(buf))
    printf("recv: [%s]\n", line);
  printf("[+] Closing client\n");
  libnet_close(fd);
  printf("[+] Done\n");
  RETURN (0);
}

void	usage(char *moul)
{
  printf("usage: %s HOSTNAME PORT\n", moul);
  exit(-1);
}
