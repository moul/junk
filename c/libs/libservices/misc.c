/**
 * libservices/misc.c
 *
 * Copyright (c) Manfred Touron 2008
 */

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>

#include "core.h"

int	services_cmpfn(void *a, void *b)
{
  return (strcmp(((svc)a)->name, b));
}
