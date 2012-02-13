#ifndef _XMALLOC_H
# define _XMALLOC_H

# include <sys/types.h>

# define _XM_PROTO	, char *, int, char *
# define _XM_ARGS	, __FILE__, __LINE__, (char *)__func__

# define _XM_FUNC_PROTO(FUNC, RET, PROTO)	RET _x ## FUNC PROTO

# define malloc(SIZE)		_xmalloc((SIZE) _XM_ARGS)
# define calloc(NUMBER, SIZE)	_xcalloc((NUMBER), (SIZE) _XM_ARGS)
# define realloc(PTR, SIZE)	_xrealloc((PTR), (SIZE) _XM_ARGS)
# define free(PTR)		_xfree((PTR) _XM_ARGS)

_XM_FUNC_PROTO(malloc, void *, (size_t _XM_PROTO));
_XM_FUNC_PROTO(calloc, void *, (size_t, size_t _XM_PROTO));
_XM_FUNC_PROTO(realloc, void *, (void *, size_t _XM_PROTO));

void	_xfree(void * _XM_PROTO);
void	show_xmalloc(void);

#endif /* !_XMALLOC_H */
