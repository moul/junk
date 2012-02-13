/**
 * liblc/lc.c
 *
 * Copyright (c) Manfred Touron 2008
 */

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

#include "core.h"

lc	lc_new(void)
{
  lc	new;

  if ((new = (void *)ALLOC(lc)) == NULL)
    perror("malloc");
  new->root = NULL;
  return (new);
}

void		lc_unset(lc lc)
{
  lc_node	node;
  lc_node	node2;

  for (node = lc->root; node; node = node2)
    {
      node2 = node->next;
      free(node);
    }
  free(lc);
  return ;
}
