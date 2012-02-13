/**
 * libnetcli/select.c
 *
 * Copyright (c) Manfred Touron 2008
 */

#include <stdio.h>
#include <netdb.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

#include <liblc/lc.h>

#include "core.h"
#include "select.h"

lc	_select_type_list;

slctcllbck	lnc_select_callback_new(const char *name, slctcllbckfn fn)
{
  slctcllbck	new;

  if ((new = ALLOC(*new)) == NULL)
    perror("malloc");
  new->name = name;
  new->fn = fn;
  return (new);
}

int	METHOD(select_type_add_callback,
	       (METHOD_ARGS, const char *name, slctcllbckfn fn))
{
  lc_push(THIS->select->type->callbacks,
	  lnc_select_callback_new(name, fn));
  return (1);
}

int	lnc_select_type_cmpfn(void *a, void *b)
{
  return (strcmp(((select_type)a)->name, (char *)b));
}

int	lnc_select_type_init(void)
{
  static int	inited = 0;

  if (!inited)
    {
      _select_type_list = lc_new();
      inited = 1;
    }
  return (1);
}

int	lnc_select_type_exists(const char *name)
{
  return (lnc_select_type_find(name) != NULL);
}

select_type	lnc_select_type_new(const char *name)
{
  select_type	new;

  if ((new = ALLOC(*name)) == NULL)
    perror("malloc");
  new->name = name;
  new->callbacks = lc_new();
  return (new);
}

select_type	lnc_select_type_find(const char *name)
{
  lnc_select_type_init();
  return (lc_find_cmpfn(_select_type_list, (void *)name,
			lnc_select_type_cmpfn));
}

int		select_type_by_fd(int fd, const char *name)
{
  select_link	link;

  if ((link = lnc_select_link_find_by_fd(fd)) == NULL)
    link = select_link_new_by_fd(fd);
  if ((link->type = lnc_select_type_find(name)) == NULL)
    link->type = lnc_select_type_new(name);
  return (1);
}

int	METHOD(select_type, (METHOD_ARGS, const char *name))
{
  if (THIS->select == NULL)
    THIS->select = select_link_new(this);
  if ((THIS->select->type = lnc_select_type_find(name)) == NULL)
    THIS->select->type = lnc_select_type_new(name);
  return (1);
}
