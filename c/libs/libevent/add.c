/**
 * libevent/add.c
 *
 * Copyright (c) Manfred Touron 2008
 */

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>

#include <liblc/liblc.h>

#include "core.h"

void	event_add_handler(const char *name, cllbck callback)
{
  event	e;

  if ((e = events_find(name)) == NULL)
    {
      e = event_new(name);
      if (!event_callback_exists(e, callback))
	lc_push(e->lc, (void *)(uintptr_t)callback);
    }
  else if (!event_callback_exists(e, callback))
    lc_push(e->lc, (void *)(uintptr_t)callback);
  return ;
}
