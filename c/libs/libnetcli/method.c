/**
 * libnetcli/lnc.c
 *
 * Copyright (c) Manfred Touron 2008
 */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#include "core.h"

int	METHOD(unset, (METHOD_ARGS))
{
  if (THIS->connected)
    close(THIS->fd);
  free(THIS);
  free(this);
  return (1);
}

int	METHOD(send, (METHOD_ARGS, char *str))
{
  int	size;

  if ((size = write(THIS->fd, str, strlen(str))) < 0)
    {
      perror("write");
      return (0);
    }
  return (size);
}

int	METHOD(read, (METHOD_ARGS, char *buf, int len))
{
  int	size;

  if ((size = read(THIS->fd, buf, len)) < 0)
    {
      perror("read");
      return (0);
    }
  return (size);
}

int	METHOD(connected, (METHOD_ARGS))
{
  return (THIS->connected);
}

int	METHOD(fd, (METHOD_ARGS))
{
  return (THIS->fd);
}
