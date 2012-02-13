/**
 * liblc/tester2.c
 *
 * Copyright (c) Manfred Touron 2008
 */

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "lc.h"

int	main(int ac, char **av)
{
  lc	lc;

  printf("[+] init\n");
  lc = lc_new();
  lc_debug(lc);

  lc_push(lc, (void *)41);
  lc_push(lc, (void *)42);
  lc_debug(lc);

  lc_push(lc, (void *)43);
  lc_debug(lc);

  lc_remove_ptr(lc, (void *)43);
  lc_debug(lc);

#if 1
  lc_push(lc, (void *)44);
  lc_debug(lc);
#endif

  printf("[+] uninit\n");
  return (0);
  (void)ac;
  (void)av;
}
