/**
 * libcfgfile/cfgfile.c
 *
 * Copyright (c) Manfred Touron 2008
 */

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

#include "core.h"

char		*cfgfile_getopt(const char *filename, char *cat,
				const char *key)
{
  cfgfile	c;

  if ((c = cfgfile_find(filename)) == NULL)
    return (NULL);
  if (_cfgfile_key_exists(c, cat, key))
    return (_cfgfile_getopt(c, cat, key));
  return (NULL);
}

int		cfgfile_cat_exists(const char *filename, char *cat)
{
  cfgfile	c;

  if ((c = cfgfile_find(filename)) == NULL)
    return (0);
  return (_cfgfile_cat_exists(c, cat));
}

int		cfgfile_key_exists(const char *filename, char *cat,
				   const char *key)
{
  cfgfile	c;

  if ((c = cfgfile_find(filename)) == NULL)
    return (0);
  if (_cfgfile_cat_exists(c, cat))
    return (_cfgfile_key_exists(c, cat, key));
  return (0);
}
