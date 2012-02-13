/**
 * libnetcli/tester.c
 *
 * Copyright (c) Manfred Touron 2008
 */

#include <stdio.h>
#include <stdlib.h>

#include "libnetcli.h"

#define BUF_SIZE	1024

void	usage(char *);

int	main(int ac, char **av)
{
  lnc	lnc;
  char	*line;

  if (ac < 3)
    usage(av[0]);
  printf ("[+] New connection to %s (%d)\n", av[1], atoi(av[2]));
  if ((lnc = lnc_connect(av[1], atoi(av[2]))) != NULL)
    {
      printf ("[+] Connected\n");
      if (!lnc->connected(lnc))
	{
	  printf("[-] Not connected...\n");
	  return (-1);
	}
      printf("[+] Send test\n");
      if (!lnc->send(lnc, "test 42\n"))
	printf("[-] Send error\n");
      if ((line = malloc(sizeof(*line) * (BUF_SIZE))) == NULL)
	{
	  perror("malloc");
	  exit(-1);
	}
      if (lnc->read(lnc, line, BUF_SIZE) < 0)
	printf("[-] Read error\n");
      else
	printf("[*] Read : [%s]\n", line);
      free(line);
      lnc->unset(lnc);
      return (0);
    }
  printf ("[-] Connect error\n");
  return (-1);
}

void	usage(char *moul)
{
  printf("usage: %s HOSTNAME PORT\n", moul);
  exit(-1);
}
