/**
 * libnetcli/tester.c
 *
 * Copyright (c) Manfred Touron 2008
 */

#include <stdio.h>
#include <stdlib.h>

#include "libnetcli.h"
#include "select.h"

#define BUF_SIZE	1024

SELECT_CALLBACK(timeout_callback)
{
  printf("timeout_callback called\n");
  (void)argv;
  (void)lnc;
}

void	usage(char *);

int	main(int ac, char **av)
{
  lnc	lnc;
  char	*line;
  slct	select;

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
      printf("[+] Set select type\n");
      lnc->select_type(lnc, "totof");

      printf("[+] Add callback to select type\n");
      lnc->select_type_add_callback(lnc, "timeout", timeout_callback);

      printf("[+] Set select type\n");
      select_type_by_fd(0, "titi");

      printf("[+] Initialise new select\n");
      select = select_new();

      printf("[+] select add stdin\n");
      select_add_fd(select, 0);

      printf("[+] select add lnc\n");
      select_add_fd(select, lnc->fd(lnc));

      printf("[+] lnc_select\n");
      printf("[+] lnc_select_call_callbacks\n");
      lnc_select(select);
      printf("[+] lnc_select end\n");

      printf("[+] lnc_select loop\n");
      lnc_select_loop(select);
      printf("[+] lnc_select loop end\n");

/*       if (lnc->read(lnc, line, BUF_SIZE) < 0) */
/* 	printf("[-] Read error\n"); */
/*       else */
/* 	printf("[*] Read : [%s]\n", line); */
/*       free(line); */
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
