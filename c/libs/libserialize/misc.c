/**
 * libserialize/misc.c
 *
 * Copyright (c) Manfred Touron 2008
 */

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

#include "core.h"

int	serialize_name_cmpfn(void *a, void *b)
{
  return (strcmp(((srlz *)a)->name, (char *)b) &&
	  strcmp(((srlz *)a)->alias, (char *)b));
}

