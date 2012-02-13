/**
 * libnetcli/select_link.c
 *
 * Copyright (c) Manfred Touron 2008
 */

#include <stdio.h>
#include <netdb.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>

#include <liblc/lc.h>
#include <librbuf/librbuf.h>

#include "core.h"
#include "select.h"

lc	_select_link_list;

int	lnc_select_link_init(void)
{
  static int	inited = 0;

  if (!inited)
    {
      _select_link_list = lc_new();
      inited = 1;
    }
  return (1);
}

select_link	select_link_new(lnc l)
{
  select_link	new;

  lnc_select_link_init();
  if ((new = ALLOC(*new)) == NULL)
    perror("malloc");
  new->lnc = l;
  new->fd = l->fd(l);
  new->type = NULL;
  new->rbuf = rbuf_new(0);
  lc_push(_select_link_list, new);
  return (new);
}

select_link	select_link_new_by_fd(int fd)
{
  select_link	new;

  lnc_select_link_init();
  if ((new = ALLOC(*new)) == NULL)
    perror("malloc");
  new->lnc = NULL;
  new->fd = fd;
  new->type = NULL;
  new->rbuf = rbuf_new(0);
  lc_push(_select_link_list, new);
  return (new);
}

int	lnc_select_link_exists(const char *name)
{
  return (lnc_select_link_find(name) != NULL);
}

select_link	lnc_select_link_find(const char *name)
{
  lnc_select_link_init();
  return (lc_find_cmpfn(_select_link_list, (void *)name,
			lnc_select_cmpfn));
}

select_link	lnc_select_link_find_by_fd(int fd)
{
  lnc_select_link_init();
  return (lc_find_cmpfn(_select_link_list, (void *)&fd,
			lnc_select_fd_cmpfn));
}
