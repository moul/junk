#ifndef _XMALLOC_H
# define _XMALLOC_H

# include <sys/types.h>

# include "common.h"

# define _XM_PROTO	, char *, int, char *

# define _XM_FUNC_PROTO(FUNC, RET, PROTO)	RET _ml_x ## FUNC PROTO

# define malloc(SIZE)		_ml_xmalloc((SIZE) _XM_ARGS)
# define calloc(NUMBER, SIZE)	_ml_xcalloc((NUMBER), (SIZE) _XM_ARGS)
# define realloc(PTR, SIZE)	_ml_xrealloc((PTR), (SIZE) _XM_ARGS)
# define free(PTR)		_ml_xfree((PTR) _XM_ARGS)

_XM_FUNC_PROTO(malloc, void *, (size_t _XM_PROTO));
_XM_FUNC_PROTO(calloc, void *, (size_t, size_t _XM_PROTO));
_XM_FUNC_PROTO(realloc, void *, (void *, size_t _XM_PROTO));

void	_ml_xfree(void * _XM_PROTO);
void	show_xmalloc(void);

#endif /* !_XMALLOC_H */
