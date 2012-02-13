/**
 * libevent/find.c
 *
 * Copyright (c) Manfred Touron 2008
 */

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

#include <liblc/liblc.h>

#include "core.h"

int	event_funcptr_cmpfn(void *a, void *b)
{
  return (a > b ? 1 : (a == b ? 0 : -1));
}

int	event_callback_exists(event event, cllbck callback)
{
  return ((lc_find_cmpfn(event->lc, (void *)(uintptr_t)callback,
			 event_funcptr_cmpfn)) != NULL);
}
