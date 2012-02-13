/**
 * librbuf/core.c
 *
 * Copyright (c) Manfred Touron 2008
 */

#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>

#include "core.h"

void	rbuf_realloc_buf(rbuf rbuf, int len)
{
  rbuf_defragmentation(rbuf);
  rbuf->bufsize = CALC_RBUF_SIZE(rbuf->size + len);
  if ((rbuf->buf = realloc(rbuf->buf, rbuf->bufsize)) == NULL)
    perror("realloc");
  memset(rbuf->buf + rbuf->posw, 0, rbuf->bufsize - rbuf->posw);
  return ;
}

void	rbuf_realloc_ret(rbuf rbuf, int len)
{
  rbuf->retsize = CALC_RBUF_SIZE(len);
  if ((rbuf->ret = realloc(rbuf->ret, rbuf->retsize)) == NULL)
    perror("realloc");
  return ;
}

void	rbuf_debug(rbuf rbuf)
{
  int	i;

  if (!rbuf->buf && !rbuf->ret)
    return ;
  write(1, "+", 1);
  for (i = 0; i < rbuf->bufsize; i++)
    write(1, "-", 1);
  write(1, "+\n|", 3);
  for (i = 0; i < rbuf->bufsize; i++)
    write(1, (rbuf->buf[i] ? rbuf->buf + i : "."), 1);
  write(1, "|\n+", 3);
  for (i = 0; i < rbuf->bufsize; i++)
    write(1, "-", 1);
  write(1, "+\n", 2);
  return ;
}

void	rbuf_remove_multiline(rbuf rbuf)
{
  int	i;

  for (i = 0; i < rbuf->bufsize; i++)
    if (rbuf->buf[i] == '\n')
      {
	if (i && rbuf->buf[i - 1] == '\r')
	  rbuf->buf[i - 1] = 0;
	rbuf->buf[i] = 0;
      }
  return ;
}

void	rbuf_defragmentation(rbuf rbuf)
{
  int	i;

  if (!rbuf->posr)
    return ;
  for (i = 0; i < rbuf->size; i++)
    {
      rbuf->buf[i + 1] = rbuf->buf[i];
      rbuf->buf[i] = rbuf->buf[rbuf->posr + i];
    }
  memset(rbuf->buf + rbuf->size, 0, rbuf->bufsize - rbuf->size);
  rbuf->posw -= rbuf->posr;
  rbuf->posr = 0;
  return ;
}
