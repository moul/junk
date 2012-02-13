/**
 * libmlutil/xmalloc.h
 *
 * Copyright (c) Manfred Touron 2008
 */

#ifndef LIBMLUTIL_XMALLOC_H
# define LIBMLUTIL_XMALLOC_H

# include <stdlib.h>
# include <stdio.h>
# include <assert.h>
# include "types.h"

# if 1
#  include <libdebugmalloc/xmalloc.h>
#  define ALLOC(X)	(X*)_ml_xmalloczero(sizeof(X) _XM_ARGS)
#  define ALLOC_N(X, N)	(X*)_ml_xmalloczero(sizeof(X) * (N) _XM_ARGS)
#  define REALLOC_N(PTR, X, S, N)				\
  (X*)_ml_xrealloczero(PTR, sizeof(X) * (S), sizeof(X) * (N) _XM_ARGS)
# else
#  define ALLOC(X)	(X*)malloczero(sizeof(X))
#  define ALLOC_N(X, N)	(X*)malloczero(sizeof(X) * (N))
#  define REALLOC_N(PTR, X, S, N)				\
  (X*)realloczero(PTR, sizeof(X) * (S), sizeof(X) * (N))
# endif


# define FREE(X)	{if(X != NULL)free(X);}

_XM_FUNC_PROTO(malloczero, void *, (size_t _XM_PROTO));
_XM_FUNC_PROTO(realloczero, void *, (void *, size_t, size_t _XM_PROTO));

extern void	*malloczero(size_t);
extern void	*realloczero(void *, size_t, size_t);

#endif /* !LIBMLUTIL_XMALLOC_H */
