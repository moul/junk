/**
 * librbuf/tester.c
 *
 * Copyright (c) Manfred Touron 2008
 */

#include <stdio.h>

#include "librbuf.h"

int	main(int ac, char **av)
{
  rbuf	rbuf;

  rbuf = rbuf_new(0);
  rbuf_debug(rbuf);
  rbuf_add(rbuf, "toto");
  rbuf_debug(rbuf);
  rbuf_add(rbuf, "pute");
  rbuf_debug(rbuf);
  rbuf_add(rbuf, "lol");
  rbuf_debug(rbuf);
  rbuf_add(rbuf, "wesh ziva");
  rbuf_debug(rbuf);
  rbuf_add(rbuf, "lolzz t'es le plus fort");
  rbuf_debug(rbuf);
  printf("     <<< [%s]\n", rbuf_get(rbuf));
  rbuf_debug(rbuf);
  printf("     <<< [%s]\n", rbuf_get(rbuf));
  rbuf_debug(rbuf);
  printf("     <<< [%s]\n", rbuf_get(rbuf));
  rbuf_debug(rbuf);
  printf("     <<< [%s]\n", rbuf_get(rbuf));
  rbuf_debug(rbuf);
  rbuf_add(rbuf, "ahah lolz");
  rbuf_debug(rbuf);
  rbuf_add(rbuf, "azertyuiop");
  rbuf_debug(rbuf);
  rbuf_add(rbuf, "0123456789");
  rbuf_debug(rbuf);
  rbuf_add(rbuf, "0123456789");
  rbuf_debug(rbuf);
  printf("     <<< [%s]\n", rbuf_get(rbuf));
  rbuf_debug(rbuf);
  printf("     <<< [%s]\n", rbuf_get(rbuf));
  rbuf_debug(rbuf);
  printf("     <<< [%s]\n", rbuf_get(rbuf));
  rbuf_debug(rbuf);
  rbuf_add(rbuf, "abcdefghijklmnopqrstuvwxyz");
  rbuf_debug(rbuf);
  rbuf_add(rbuf, "abcdefghijklmnopqrstuvwxyz");
  rbuf_debug(rbuf);
  rbuf_add(rbuf, "abcdefghijklmnopqrstuvwxyz");
  rbuf_debug(rbuf);
  rbuf_add(rbuf, "abcdefghijklmnopqrstuvwxyz");
  rbuf_debug(rbuf);
  rbuf_debug(rbuf);
  rbuf_unset(rbuf);
  printf("     <<< [%s]\n", rbuf_get(rbuf));
  rbuf_debug(rbuf);
  return (0);
  (void)ac;
  (void)av;
}
