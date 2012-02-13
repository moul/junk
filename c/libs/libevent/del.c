/**
 * libevent/del.c
 *
 * Copyright (c) Manfred Touron 2008
 */

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

#include <liblc/liblc.h>

#include "core.h"

void		event_callback_delete(event e, cllbck callback)
{
  lc_remove_ptr(e->lc, (void *)(uintptr_t)callback);
  if (!lc_length(e->lc))
    event_unset(e);
  return ;
}

void	event_del_handler(const char *name, cllbck callback)
{
  event	e;

  e = events_find(name);
  if (event_callback_exists(e, callback))
    event_callback_delete(e, callback);
  return ;
}
