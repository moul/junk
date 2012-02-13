/**
 * libcfgfile/core.c
 *
 * Copyright (c) Manfred Touron 2008
 */

#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>

#include "core.h"

int	cfgfile_cmpfn(void *a, void *b)
{
  return (strcmp(((cfgfile)a)->filename, (char *)b));
}
