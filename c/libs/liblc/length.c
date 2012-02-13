/**
 * liblc/length.c
 *
 * Copyright (c) Manfred Touron 2008
 */

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#include "core.h"

int		lc_length(lc lc)
{
  int		i;
  lc_node	node;

  i = 0;
  for (node = lc->root; node; node = node->next)
    i++;
  return (i);
}
