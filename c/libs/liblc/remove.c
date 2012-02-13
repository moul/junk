/**
 * liblc/remove.c
 *
 * Copyright (c) Manfred Touron 2008
 */

#include <stdarg.h>

#include "core.h"

int		lc_remove(lc lc, lc_node node)
{
  lc_node	tmp;

  for (tmp = lc->root; tmp; tmp = tmp->next)
    if (tmp == node)
      {
	lc_node_unset(lc, tmp);
	return (1);
      }
  return (0);
}

int		lc_remove_ptr(lc lc, void *ptr)
{
  lc_node	tmp;

  for (tmp = lc->root; tmp; tmp = tmp->next)
    if (tmp->ptr == ptr)
      {
	lc_node_unset(lc, tmp);
	return (1);
      }
  return (0);
}

int		lc_remove_nolimit(lc lc, lc_node node)
{
  lc_node	tmp;
  int		ret;

  ret = 0;
  for (tmp = lc->root; tmp; tmp = tmp->next)
    if (tmp == node)
      {
	lc_node_unset(lc, tmp);
	ret++;
      }
  return (ret);
}

int		lc_remove_ptr_nolimit(lc lc, void *ptr)
{
  lc_node	tmp;
  int		ret;

  ret = 0;
  for (tmp = lc->root; tmp; tmp = tmp->next)
    if (tmp->ptr == ptr)
      {
	lc_node_unset(lc, tmp);
	ret++;
      }
  return (ret);
}
