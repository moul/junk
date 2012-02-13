/**
 * libserialize/serialize_do.c
 *
 * Copyright (c) Manfred Touron 2008
 */

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

#include <liblc/lc.h>

#include "core.h"

char	*serialize(void *ptr, const char *type)
{
  srlz	*s;
  char	*out;

  out = "";
  s = serialize_get(type);
  if (s)
    {
      printf("[+] srlz \"%s\" found\n", type);
    }
  else
    printf("Cannot find informations about structure \"%s\"\n", type);
  return (NULL);
  (void)ptr;
}
