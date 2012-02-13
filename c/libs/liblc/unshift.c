/**
 * liblc/unshift.c
 *
 * Copyright (c) Manfred Touron 2008
 */

#include <stdarg.h>

#include "core.h"

lc		lc_unshift(lc lc, void *ptr)
{
  lc_node	new;
  lc_node	last;

  if (lc->root)
    {
      last = (lc->root->prev ? lc->root->prev : lc->root);
      new = lc_node_new(ptr, lc->root->prev, lc->root);
      lc->root->prev = new;
      lc->root = new;
    }
  else
    lc->root = lc_node_new(ptr, NULL, NULL);
  return (lc);
}

lc		lc_unshiftn(lc lc, int count, ...)
{
  va_list	varg;

  va_start(varg, count);
  while (count--)
    lc_unshift(lc, va_arg(varg, void *));
  va_end(varg);
  return (lc);
}
