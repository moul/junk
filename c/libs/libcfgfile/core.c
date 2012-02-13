/**
 * libcfgfile/core.c
 *
 * Copyright (c) Manfred Touron 2008
 */

#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>

#include <liblc/lc.h>

#include <librbuf/librbuf.h>

#include "core.h"

lc	_cfgfile_list;

cfgfile		cfgfile_find(const char *name)
{
  cfgfile	c;

  cfgfile_init();
  if ((c = lc_find_cmpfn(_cfgfile_list, (void *)name,
			 cfgfile_cmpfn)) != NULL)
    return (c);
  return (cfgfile_new(name));
}

void	cfgfile_init(void)
{
  static int	inited = 0;

  if (!inited)
    {
      _cfgfile_list = lc_new();
      inited = 1;
    }
  return ;
}

cfgfile	cfgfile_new(const char *filename)
{
  cfgfile	new;

  cfgfile_init();
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
