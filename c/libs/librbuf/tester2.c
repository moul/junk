/**
 * librbuf/tester2.c
 *
 * Copyright (c) Manfred Touron 2008
 */

#include <stdio.h>

#include "librbuf.h"

int	main(int ac, char **av)
{
  rbuf	rbuf;
  char	*line;
  int	i;

  rbuf = rbuf_new(0);

  printf("=====\n");
  rbuf_add(rbuf, "toto");
  rbuf_add(rbuf, "pute");
  rbuf_add(rbuf, "lol");
  rbuf_add(rbuf, "wesh ziva");
  rbuf_add(rbuf, "lolzz t'es le plus fort");
  while ((line = rbuf_get(rbuf)))
    printf("[%s]\n", line);

  printf("=====\n");
  rbuf_add(rbuf, "wesh ziva");
  for (i = 0; i < 10; i++)
    rbuf_add(rbuf, "bambi est joli");
  rbuf_add(rbuf, "wesh ziva");
  while ((line = rbuf_get(rbuf)))
    printf("[%s]\n", line);

#if 0
  rbuf_debug(rbuf);
#endif

  printf("=====\n");
  rbuf_add(rbuf, "totopute");
  printf("[%s]\n", rbuf_get(rbuf));
  rbuf_add(rbuf, "totopu\n");
  printf("[%s]\n", rbuf_get(rbuf));
  rbuf_add(rbuf, "toto");
  printf("[%s]\n", rbuf_get(rbuf));
  rbuf_add(rbuf, "tata");
  printf("[%s]\n", rbuf_get(rbuf));
  rbuf_add(rbuf, "totopu");
  printf("[%s]\n", rbuf_get(rbuf));

#if 0
  rbuf_debug(rbuf);
#endif

  printf("=====\n");
  rbuf_unset(rbuf);
  return (0);
  (void)ac;
  (void)av;
}
