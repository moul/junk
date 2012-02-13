/**
 * libevent/call.c
 *
 * Copyright (c) Manfred Touron 2008
 */

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

#include <liblc/liblc.h>

#include "core.h"

int		event_call_walk(void *ptr, int argc, va_list varg)
{
  return (((int (*)(int, va_list))(uintptr_t)ptr)(argc, varg));
}

int		event_call_walk_a(void *ptr, CLLBCK_ARGS argv)
{
  return (((int (*)(CLLBCK_ARGS))(uintptr_t)ptr)(argv));
}

int		event_call(const char *name, CLLBCK_ARGS argv)
{
  event		e;
  int		ret;

  ret = 1;
  if ((e = events_find(name)) == NULL)
    return (0);
  ret *= !!lc_walk_a(e->lc, event_call_walk_a, argv);
  return (ret);
}
