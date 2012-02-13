#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define _XM_PROTO		, char *, int, char *
#define _XM_ARGS		, file, line, func
#define _XM_PROTO_FULL		, char *file, int line, char *func

#define NOTHING			(void)0;

void	(*_f_xmalloc_add)(void *, char *, size_t _XM_PROTO) = NULL;
void	(*_f_xmalloc_del)(void * _XM_PROTO) = NULL;
void	(*_f_xmalloc_show)(void) = NULL;

# define _XM_CALL(FUNC, ARGS)	{ if (FUNC != NULL) { FUNC ARGS; } }
# define _XM_DEL(PTR)	if (ptr != NULL) {	\
    _XM_CALL(_f_xmalloc_del, (ptr _XM_ARGS)) }

# define _XM_FUNC(FUNC, RET, PROTO, ARGS, DELETE)			\
  void	*_x ## FUNC PROTO						\
  {									\
    RET	ret;								\
									\
    if ((ret = (RET)FUNC ARGS) == NULL)					\
      {									\
	(void)perror(#FUNC);						\
	(void)abort();							\
      }									\
    _XM_CALL(_f_xmalloc_add,						\
	     ((void *)ret, #FUNC, size _XM_ARGS));			\
    DELETE;								\
    return (ret);							\
  }

_XM_FUNC(malloc, void *, (size_t size _XM_PROTO_FULL), (size), NOTHING)
_XM_FUNC(calloc, void *, (size_t number, size_t size _XM_PROTO_FULL),
	 (number, size), NOTHING)
_XM_FUNC(realloc, void *, (void *ptr, size_t size _XM_PROTO_FULL),
	 (ptr, size), _XM_DEL(ptr))

void	_xfree(void *ptr _XM_PROTO_FULL)
{
  free(ptr);
  _XM_CALL(_f_xmalloc_del, (ptr _XM_ARGS));
}

void	show_xmalloc(void)
{
  _XM_CALL(_f_xmalloc_show, ());
  return ;
}
