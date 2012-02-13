/**
 * librbuf/librbuf.h
 *
 * Copyright (c) Manfred Touron 2008
 */

#ifndef LIBRBUF_H
# define LIBRBUF_H

# include <stdarg.h>

typedef struct	s_rbuf
{
  int		bufsize;
  int		retsize;

  int		multiline;

  int		posr;
  int		posw;
  int		size;

  char		*buf;
  char		*ret;
}		*rbuf;

rbuf	rbuf_new(int);
int	rbuf_add(rbuf, char *);
int	rbuf_addn(rbuf, char *, int);
char	*rbuf_get(rbuf);
void	rbuf_unset(rbuf);
void	rbuf_reset(rbuf);
int	rbuf_read(int, rbuf, int);
int	rbuf_eof(rbuf);
int	rbuf_vprintf(rbuf, char *, va_list);
int	rbuf_printf(rbuf, char *, ...);

#endif /* !LIBRBUF_H */
