/**
 * libevent/events.c
 *
 * Copyright (c) Manfred Touron 2008
 */

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

#include <liblc/liblc.h>

#include "core.h"

lc	events = NULL;

int	events_init(void)
{
  static int	inited = 0;

  if (!inited)
    {
      events = lc_new();
      inited = 1;
    }
  return (1);
}

int	events_event_cmpfn(void *a, void *b)
{
  event	e;

  e = (event)a;
  return (strcmp(e->name, b));
}

int	events_event_exists(event e)
{
  return (events_find(e->name) != NULL);
}

event	events_add(event e)
{
  events_init();
  lc_push(events, e);
  return (e);
}

void	event_unset(event e)
{
  lc_remove_ptr(events, e);
  free(e);
  return ;
}

void	events_debug(void)
{
  if (events)
    lc_walk(events, event_e_debug);
}

event	events_find(const char *name)
{
  events_init();
  return ((lc_find_cmpfn(events, (void *)name,
			 events_event_cmpfn)));
}
