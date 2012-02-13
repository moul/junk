#ifndef _XMALLOC_CORE_H
# define _XMALLOC_CORE_H

# include "common.h"

#define _XM_PROTO		, char *, int, char *
#define _XM_ARGS_		, file, line, func
#define _XM_PROTO_FULL		, char *file, int line, char *func

#define NOTHING			(void)0;

# define _XM_CALL(FUNC, ARGS)	{ if (FUNC != NULL) { FUNC ARGS; } }
# define _XM_DEL(PTR)	if (ptr != NULL) {	\
    _XM_CALL(_f_xmalloc_del, (ptr _XM_ARGS)) }

# define _XM_FUNC(FUNC, RET, PROTO, ARGS, DELETE)			\
  void	*_ml_x ## FUNC PROTO						\
  {									\
    RET	ret;								\
									\
    if ((ret = (RET)FUNC ARGS) == NULL)					\
      {									\
	(void)perror(#FUNC);						\
	(void)abort();							\
      }									\
    _XM_CALL(_f_xmalloc_add,						\
	     ((void *)ret, #FUNC, size _XM_ARGS_));			\
    DELETE;								\
    return (ret);							\
  }

#endif
