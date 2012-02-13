/**
 * libwebsite/environ.c
 *
 * Copyright (c) Manfred Touron 2008
 */

#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

#include "core.h"
#include "environ.h"

extern char	**environ;

int	ws_print_environ(void)
{
  int	i;

  for (i = 0; environ[i]; i++)
    printf("env:%d [%s]\n", i, environ[i]);
  return (1);
}

char	*ws_get_environ(const char *name)
{
  char	*value;
  int	i;
  int	s;

  s = strlen(name);
  for (i = 0; environ[i]; i++)
    if (!strncmp(name, environ[i], s))
      return (environ[i] + s);
  return (NULL);
}
