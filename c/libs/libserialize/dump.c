/**
 * libserialize/dump.c
 *
 * Copyright (c) Manfred Touron 2008
 */

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

#include <liblc/lc.h>

#include "core.h"

int	serialize_dump(const char *name)
{
  srlz	*s;

  s = serialize_get(name);
  if (s)
    {
      printf("struct %s %s;\n", s->name, s->content);
      if (s->alias)
	printf("typedef struct %s %s;\n", s->name, s->alias);
      else
	printf("no typedef for struct %s\n", s->name);
      return (1);
    }
  printf("Cannot find informations about structure \"%s\"\n", name);
  return (0);
}
