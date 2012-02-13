/**
 * liblc/debug.c
 *
 * Copyright (c) Manfred Touron 2008
 */

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#include "core.h"

void		lc_debug(lc lc)
{
  lc_node	node;

  printf("+--------------------------------"
	 "-------------------------------+\n");
  printf("\t\t\t\t\t\t\t\t|\r| lc: %p, root: %p\n",
	 (void *)lc, (void *)lc->root);
  for (node = lc->root; node; node = node->next)
    printf("\t\t\t\t\t\t\t\t|\r| node: %p, prev: %p, next: %p, ptr: %p\n",
	   (void *)node, (void *)node->prev,
	   (void *)node->next, node->ptr);
  printf("+--------------------------------"
	 "-------------------------------+\n");
  return ;
}
