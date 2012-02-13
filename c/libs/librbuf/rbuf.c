/**
 * librbuf/rbuf.c
 *
 * Copyright (c) Manfred Touron 2008
 */

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

#include <libmlutil/string.h>
#include <libmlutil/xmalloc.h>
#include <libmlutil/debug.h>

#include "core.h"

rbuf	rbuf_new(int multiline)
{
  rbuf	new;

  DEBUG_ASCII_IN;
  if ((new = ALLOC(struct s_rbuf)) == NULL)
    perror("malloc");
  new->buf = NULL;
  new->multiline = multiline;
  new->bufsize = 0;
  new->ret = NULL;
  new->retsize = 0;
  rbuf_reset(new);
  RETURN (new);
}

int	rbuf_read(int fd, rbuf rbuf, int size)
{
  int	ret;

  DEBUG_ASCII_IN;
  if (rbuf->size + size >= rbuf->bufsize)
    rbuf_realloc_buf(rbuf, size);
  if (rbuf->posw + size >= rbuf->bufsize)
    rbuf_defragmentation(rbuf);
  ret = read(fd, rbuf->buf + rbuf->posw, size);
  rbuf->buf[rbuf->posw + ret] = 0;
  if (!rbuf->multiline)
    rbuf_remove_multiline(rbuf);
  rbuf->size += ret + 1;
  rbuf->posw += ret + 1;
  RETURN (ret);
}

int	rbuf_eof(rbuf rbuf)
{
  DEBUG_ASCII_IN;
  DEBUG_ASCII(0, "rbuf->size: %d", rbuf->size);
  RETURN (!rbuf->size);
}

int		rbuf_printf(rbuf rbuf, char *fmt, ...)
{
  int		ret;
  va_list	varg;

  DEBUG_ASCII_IN;
  va_start(varg, fmt);
  ret = rbuf_vprintf(rbuf, fmt, varg);
  va_end(varg);
  RETURN (ret);
}

int		rbuf_vprintf(rbuf rbuf, char *fmt, va_list varg)
{
  static char	*tmp = NULL;
  int		size;

  DEBUG_ASCII_IN;
  size = vprintflen(fmt, varg);
  tmp = REALLOC_N(tmp, char, 0, size);
  vsnprintf(tmp, size + 1, fmt, varg);
  rbuf_add(rbuf, tmp);
  RETURN (size);
}

int	rbuf_add(rbuf rbuf, char *src)
{
  int	ret;
  DEBUG_ASCII_IN;
  ret = rbuf_addn(rbuf, src, strlen((char *)src));
  RETURN (ret);
}

int	rbuf_addn(rbuf rbuf, char *src, int size)
{
  DEBUG_ASCII_IN;
  if (rbuf->size + size >= rbuf->bufsize)
    rbuf_realloc_buf(rbuf, size);
  if (rbuf->posw + size >= rbuf->bufsize)
    rbuf_defragmentation(rbuf);
  memmove(rbuf->buf + rbuf->posw, src, size);
  rbuf->buf[rbuf->posw + size] = 0;
  if (!rbuf->multiline)
    rbuf_remove_multiline(rbuf);
  rbuf->size += size + 1;
  rbuf->posw += size + 1;
  RETURN (size);
}

char	*rbuf_get(rbuf rbuf)
{
  int	len;

  DEBUG_ASCII_IN;
  if ((!rbuf->buf && !rbuf->ret) || !rbuf->size)
    RETURN (NULL);
  len = strlen(rbuf->buf + rbuf->posr);
  if (len >= rbuf->retsize)
    rbuf_realloc_ret(rbuf, len);
  memcpy(rbuf->ret, rbuf->buf + rbuf->posr, len);
  rbuf->ret[len] = 0;
  rbuf->posr += len + 1;
  rbuf->size -= (len + 1);
  while (rbuf->size && !rbuf->buf[rbuf->posr])
    {
      rbuf->posr++;
      rbuf->size--;
    }
  if (rbuf->size && !rbuf->buf[rbuf->posr + 1])
    {
      rbuf->posr++;
      rbuf->size--;
    }

  RETURN (rbuf->ret);
}

void	rbuf_unset(rbuf rbuf)
{
  DEBUG_ASCII_IN;
  rbuf_reset(rbuf);
  if (rbuf->buf)
    free(rbuf->buf);
  rbuf->buf = NULL;
  if (rbuf->ret)
    free(rbuf->ret);
  rbuf->ret = NULL;
  free(rbuf);
  RETURN_VOID;
}

void	rbuf_reset(rbuf rbuf)
{
  DEBUG_ASCII_IN;
  rbuf->posr = 0;
  rbuf->posw = 0;
  rbuf->size = 0;
  memset(rbuf->buf, 0, rbuf->bufsize);
  RETURN_VOID;
}
