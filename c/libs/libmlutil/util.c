/**
 * libmlutil/util.c
 *
 * Copyright (c) Manfred Touron 2008
 */

#include <string.h>

#include "debug.h"
#include "util.h"
#include "misc.h"

static const char	*progname = NULL;

void	libmlutil_init(int ac, char **av)
{
  DEBUG_ASCII_IN;
  progname = av[0];
  RETURN_VOID;
  (void)ac;
}

const char	*libmlutil_progname(void)
{
  DEBUG_ASCII_IN;
  RETURN (progname);
}

const char	*libmlutil_progbasename(void)
{
  const char	*s;

  DEBUG_ASCII_IN;
  s = strrchr(progname, '/');
  RETURN (s == NULL ? progname : s + 1);
}
