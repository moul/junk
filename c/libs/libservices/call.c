/**
 * libservices/call.c
 *
 * Copyright (c) Manfred Touron 2008
 */

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>

#include <liblc/lc.h>

#include "core.h"

char	*service_call(const char *name, VARGS_T argv)
{
  svc	service;

  if ((service = service_find(name)) != NULL)
    return (service->fn(argv));
  return (NULL);
}

int	service_exists(const char *name)
{
  return (name && strlen(name) && service_find(name) != NULL);
}
