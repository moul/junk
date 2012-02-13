/**
 * libselect/core.c
 *
 * Copyright (c) Manfred Touron 2008
 */

#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>

#include <liblc/lc.h>

#include "core.h"

lc	_select_list;

select		select_find(const char *name)
{
  select	c;

  select_init();
  if ((c = lc_find_cmpfn(_select_list, (void *)name,
			 select_cmpfn)) != NULL)
    return (c);
  return (select_new(name));
}

void	select_init(void)
{
  static int	inited = 0;

  if (!inited)
    {
      _select_list = lc_new();
      inited = 1;
    }
  return ;
}

select	select_new(const char *filename)
{
  select	new;

  select_init();
  if ((new = ALLOC(*new)) == NULL)
    {
      perror("malloc");
      exit (-1);
    }
  new->filename = filename;
  new->fd = open(filename, O_RDONLY);
  new->rbuf = rbuf_new(0);
  return (new);
}
