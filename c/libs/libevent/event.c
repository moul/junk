/**
 * libevent/event.c
 *
 * Copyright (c) Manfred Touron 2008
 */

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

#include <liblc/liblc.h>

#include "core.h"

event	event_new(const char *name)
{
  event	new;

  if ((new = ALLOC(event)) == NULL)
    perror("malloc");
  new->name = name;
  new->lc = lc_new();
  events_add(new);
  return (new);
}
