/**
 * liblc/each.c
 *
 * Copyright (c) Manfred Touron 2008
 */

#include "core.h"

int		lc_walk(lc lc, walkfn fn)
{
  lc_node	node;
  int		ret;

  ret = 1;
  for (node = lc->root; node; node = node->next)
    {
      ret *= !!fn(node->ptr);
      if (node->next == lc->root)
	break;
    }
  return (ret);
}

int		lc_walk_v(lc lc, walkfnv fn, int argc, va_list varg)
{
  lc_node	node;
  int		ret;

  ret = 1;
  for (node = lc->root; node; node = node->next)
    {
      ret *= !!fn(node->ptr, argc, varg);
      if (node->next == lc->root)
	break;
    }
  return (ret);
}

int		lc_walk_a(lc lc, walkfna fn, CLLBCK_ARGS argv)
{
  lc_node	node;
  int		ret;

  ret = 1;
  for (node = lc->root; node; node = node->next)
    {
      ret *= !!fn(node->ptr, argv);
      if (node->next == lc->root)
	break;
    }
  return (ret);
}
