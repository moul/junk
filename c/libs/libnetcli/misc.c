/**
 * libnetcli/misc.c
 *
 * Copyright (c) Manfred Touron 2008
 */

#include <stdio.h>
#include <netdb.h>
#include <stddef.h>
#include <string.h>

#include <liblc/lc.h>

#include "core.h"
#include "select.h"

int	lnc_select_cmpfn(void *a, void *b)
{
  return (strcmp(((select_type)a)->name, (char *)b));
}

int	lnc_select_fd_cmpfn(void *a, void *b)
{
  return ((select_link)a)->fd != (((int *)b)[0]);
}
