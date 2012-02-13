#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "core.h"

void	(*_f_xmalloc_add)(void *, char *, size_t _XM_PROTO) = NULL;
void	(*_f_xmalloc_del)(void * _XM_PROTO) = NULL;
void	(*_f_xmalloc_show)(void) = NULL;

_XM_FUNC(malloc, void *, (size_t size _XM_PROTO_FULL), (size), NOTHING)
_XM_FUNC(calloc, void *, (size_t number, size_t size _XM_PROTO_FULL),
	 (number, size), NOTHING)
_XM_FUNC(realloc, void *, (void *ptr, size_t size _XM_PROTO_FULL),
	 (ptr, size), _XM_DEL(ptr))

void	_ml_xfree(void *ptr _XM_PROTO_FULL)
{
  free(ptr);
  _XM_CALL(_f_xmalloc_del, (ptr _XM_ARGS));
}

void	show_xmalloc(void)
{
  _XM_CALL(_f_xmalloc_show, ());
  return ;
}
