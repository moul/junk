/**
 * libmlutil/misc.c
 *
 * Copyright (c) Manfred Touron 2008
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <libdebugmalloc/core.h>

#include "output.h"

extern void	(*_f_xmalloc_add)(void *, char *, size_t _XM_PROTO);
extern void	(*_f_xmalloc_del)(void * _XM_PROTO);
extern void	(*_f_xmalloc_show)(void);

void	*malloczero(size_t size)
{
  void	*ptr;

  if ((ptr = malloc(size)) == NULL)
    warn_err();
  else
    memset(ptr, 0, size);
  return (ptr);
}

void	*realloczero(void *ptr, size_t old, size_t new)
{
  void	*p;

  p = NULL;
  if (new)
    {
      p = realloc(ptr, new);
      if (p == NULL)
	{
	  warn_err();
	  return (NULL);
	}
      if (new > old)
	memset((char *)p + old, 0, new - old);
    }
  return (p);
}

_XM_FUNC(malloczero, void *, (size_t size _XM_PROTO_FULL), (size), NOTHING)
_XM_FUNC(realloczero, void *, (void *ptr, size_t old, size_t size	\
			       _XM_PROTO_FULL), (ptr, old, size),	\
	 _XM_DEL(ptr))

