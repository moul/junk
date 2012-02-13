/**
 * libmlutil/debug.c
 *
 * Copyright (c) Manfred Touron 2008
 */

#include <unistd.h>
#include <stdio.h>

#include "debug.h"

#if defined __DEBUG_LIBMLUTIL || 1
void	(*mlutil_status_fn)(const char *, va_list) = _status_fn_def;
#else
void	(*mlutil_status_fn)(const char *, va_list) = NULL;
#endif

void		debug_ascii_v(char *file, int line, char *func,
			      int pad, char *str, va_list varg)
{
  static int	left = 0;
  int		i;

  if (pad > 0)
    left += pad;
  for (i = 0; i < left; i++)
    write(1, " ", 1);
  printf("%s ", (pad > 0 ? "\\" : (pad < 0 ? "/" : "*")));
  vprintf(str, varg);
  printf(" (%s:%d %s)\n", file, line, func);
  if (pad < 0)
    left += pad;
  return;
}

void		debug_ascii(char *file, int line, char *func,
			    int pad, char *str, ...)
{
  va_list	varg;

  va_start(varg, str);
  debug_ascii_v(file, line, func, pad, str, varg);
  va_end(varg);
  return ;
}

void		status(const char *fmt, ...)
{
  va_list	varg;

  va_start(varg, fmt);
  if (mlutil_status_fn)
    mlutil_status_fn(fmt, varg);
  va_end(varg);
  return ;
}

void		_status_fn_def(const char *fmt, va_list varg)
{
  vprintf(fmt, varg);
  printf("\n");
}
