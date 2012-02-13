/**
 * libservices/add.c
 *
 * Copyright (c) Manfred Touron 2008
 */

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>

#include <liblc/lc.h>

#include "core.h"

lc	_services_list = NULL;

void	services_init(void)
{
  static int	inited = 0;

  if (!inited)
    {
      _services_list = lc_new();
      inited = 1;
    }
  return ;
}

int	service_list_walkfn(void *a)
{
  printf("| %s: %s\n", ((svc)a)->name, ((svc)a)->descr);
  return (1);
}

svc	service_find(const char *name)
{
  services_init();
  return ((lc_find_cmpfn(_services_list, (void *)name,
			 services_cmpfn)));
}

void	services_list(void)
{
  services_init();
  printf("+---------------------------------------------\n");
  lc_walk(_services_list, service_list_walkfn);
  printf("+---------------------------------------------\n");
  return ;
}

int	service_add(const char *name, svcfn fn, const char *descr)
{
  svc	new;

  services_init();
  new = ALLOC(*new);
  new->name = name;
  new->fn = fn;
  new->descr = descr;
  lc_push(_services_list, new);
  return (1);
}
