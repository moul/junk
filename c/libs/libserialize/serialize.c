/**
 * libserialize/serialize.c
 *
 * Copyright (c) Manfred Touron 2008
 */

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

#include <liblc/lc.h>

#include "core.h"

lc	_serializes_list = NULL;

int		serialize_init(void)
{
  static int	inited = 0;

  if (!inited)
    {
      inited = 1;
      _serializes_list = lc_new();
    }
  return (1);
}

void	serialize_add(char *name, char *content, char *alias)
{
  srlz	*s;

  serialize_init();
  if ((s = ALLOC(*s)) == NULL)
    perror("malloc");
  s->name = name;
  s->content = content;
  s->alias = alias;
  lc_push(_serializes_list, s);
  return ;
}

int	print_walk(void *ptr)
{
  printf("print_walk: [%s]\n", ((srlz *)ptr)->name);
  return (1);
}

srlz	*serialize_get(const char *name)
{
  return (lc_find_cmpfn(_serializes_list,
			(void *)name, serialize_name_cmpfn));
}
