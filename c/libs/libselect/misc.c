/**
 * libselect/core.c
 *
 * Copyright (c) Manfred Touron 2008
 */

#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>

#include "core.h"

int	select_cmpfn(void *a, void *b)
{
  return (strcmp(((select)a)->filename, (char *)b));
}
