/**
 * libcfgfile/parse.c
 *
 * Copyright (c) Manfred Touron 2008
 */

#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>

#include <liblc/lc.h>

#include "core.h"

char		*_cfgfile_getopt(cfgfile c, char *cat, const char *key)
{
  char		*line;

  lseek(c->fd, 0, SEEK_SET);
  while (rbuf_read(c->fd, c->rbuf, BUF_SIZE))
    ;
  while ((line = rbuf_get(c->rbuf)))
    if (strlen(line) > 1 && line[0] != '#')
      if (!strncmp(line, cat, strlen(cat)) && line[strlen(cat)] == '.')
	if (!strncmp(line + strlen(cat) + 1, key, strlen(key)) &&
	    line[strlen(cat)] == '.')
	  return (strchr(line, '=') + 1);
  return (NULL);
}

int		_cfgfile_cat_exists(cfgfile c, char *cat)
{
  char		*line;

  lseek(c->fd, 0, SEEK_SET);
  while (rbuf_read(c->fd, c->rbuf, BUF_SIZE))
    ;
  while ((line = rbuf_get(c->rbuf)))
    if (strlen(line) > 1 && line[0] != '#')
      if (!strncmp(line, cat, strlen(cat)) && line[strlen(cat)] == '.')
	return (1);
  return (0);
}

int		_cfgfile_key_exists(cfgfile c, char *cat, const char *key)
{
  char		*line;

  lseek(c->fd, 0, SEEK_SET);
  while (rbuf_read(c->fd, c->rbuf, BUF_SIZE))
    ;
  while ((line = rbuf_get(c->rbuf)))
    if (strlen(line) > 1 && line[0] != '#')
      if (!strncmp(line, cat, strlen(cat)) && line[strlen(cat)] == '.')
	if (!strncmp(line + strlen(cat) + 1, key, strlen(key)) &&
	    line[strlen(cat)] == '.')
	  return (1);
  return (0);
}
