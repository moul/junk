/**
 * liblc/lc_node.c
 *
 * Copyright (c) Manfred Touron 2008
 */

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

#include "core.h"

lc_node		lc_node_new(void *ptr, lc_node prev, lc_node next)
{
  lc_node	new;

  if ((new = (void *)ALLOC(lc_node)) == NULL)
    perror("malloc");
  new->ptr = ptr;
  new->prev = prev;
  new->next = next;
  return (new);
}

void	lc_node_unset(lc lc, lc_node node)
{
  if (node->prev && node->prev->next == node)
    node->prev->next = node->next;
  if (node->next)
    node->next->prev = node->prev;
  else
    lc->root->prev = node->prev;
  if (node == lc->root)
    lc->root = node->next;
  free(node);
  return ;
  (void)lc;
}
