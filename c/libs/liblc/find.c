/**
 * liblc/find.c
 *
 * Copyright (c) Manfred Touron 2008
 */

#include "core.h"

void		*lc_find_cmpfn(lc lc, void *ptr, cmpfn2v fn)
{
  lc_node	node;

  for (node = lc->root; node; node = node->next)
    if (!fn(node->ptr, ptr))
      return (node->ptr);
  return (NULL);
}
