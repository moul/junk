/**
 * libevent/debug.c
 *
 * Copyright (c) Manfred Touron 2008
 */

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

#include <liblc/liblc.h>

#include "core.h"

int	event_e_debug(void *ptr)
{
  event	e;

  e = ptr;
  if (e == NULL)
    return (0);
  printf("name: %s, length: %d\n",
	 e->name, lc_length(e->lc));
  return (1);
}

void	event_debug(const char *name)
{
  event_e_debug(events_find(name));
  return ;
}
