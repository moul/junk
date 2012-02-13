/**
 * libnetcli/lnc.c
 *
 * Copyright (c) Manfred Touron 2008
 */

#include <stdlib.h>
#include <stdio.h>

#include "core.h"

lnc_v	lnc_v_new(void)
{
  lnc_v	new;

  if ((new = ALLOC(*new)) == NULL)
    perror("malloc");
  new->connected = 0;
  return (new);
}

lnc	lnc_new(void)
{
  lnc	lnc;

  if ((lnc = ALLOC(*lnc)) == NULL)
    perror("malloc");
  lnc->v = lnc_v_new();
  METHOD_ADD(unset);
  METHOD_ADD(send);
  METHOD_ADD(read);
  METHOD_ADD(connected);
  METHOD_ADD(fd);
  METHOD_ADD(select_type);
  METHOD_ADD(select_type_add_callback);
  V(lnc)->select = NULL;
  return (lnc);
}
