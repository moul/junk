/**
 * liblc/tester.c
 *
 * Copyright (c) Manfred Touron 2008
 */

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "lc.h"

int	print_walk(void *ptr, int argc, va_list varg)
{
  printf("print_walk: [%s]\n", (char *)ptr);
  return (1);
  (void)argc;
  (void)varg;
}

int	main(int ac, char **av)
{
  lc	lc;
  char	*ptr;
  char	*ptr2;
  char	*ptr3;

  printf("[+] init\n");
  lc = lc_new();
  lc_debug(lc);
  lc_push(lc, "toto");
  lc_debug(lc);
  ptr = "toto2";
  ptr2 = "toto3";
  ptr3 = "toto4";
  lc_push(lc, ptr);
  lc_debug(lc);
  lc_push(lc, ptr2);
  lc_debug(lc);
  lc_push(lc, ptr3);
  lc_debug(lc);
  lc_pushn(lc, 3, ptr3, "toto5", "toto6");
  lc_walk(lc, print_walk, 0);
  lc_debug(lc);
  lc_unshift(lc, "bla");
  lc_walk(lc, print_walk, 0);
  lc_debug(lc);
  lc_unshift(lc, "bla");
  lc_walk(lc, print_walk, 0);
  lc_debug(lc);
  lc_unshift(lc, "bla");
  lc_walk(lc, print_walk, 0);
  lc_debug(lc);
  printf("shift : [%s]\n", (char *)lc_shift(lc));
  printf("shift : [%s]\n", (char *)lc_shift(lc));
  printf("shift : [%s]\n", (char *)lc_shift(lc));
  lc_debug(lc);
  lc_walk(lc, print_walk, 0);
  lc_remove_ptr(lc, ptr3);
  lc_debug(lc);
  lc_walk(lc, print_walk, 0);
/*   lc_unshiftn(lc, 3, "bli", "blo", "blu"); */
/*   lc_walk(lc, print_walk, 0); */
  lc_debug(lc);
  printf("length: %d\n", lc_length(lc));
  printf("[+] uninit\n");
  return (0);
  (void)ac;
  (void)av;
}
