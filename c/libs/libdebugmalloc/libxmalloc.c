/**
 * libxmalloc.c
 *
 * Copyright (c) Manfred Touron 2008x
 */

#include <sys/types.h>
#include <stdio.h>
#include <dlfcn.h>

# define _XM_PROTO	, char *, int, char *
# define _XM_ARGS	, file, line, func
# define _XM_PROTO_F	, char *file, int line, char *func
# define _XM_PRINTF	"(%s:%d %s)"

# define REAL(FUNC, RET_TYPE, ARGS_PROTO, ARGS_PARAM)			\
  RET_TYPE		_xm_real_ ## FUNC ARGS_PROTO			\
  {									\
    static RET_TYPE	(*func)ARGS_PROTO;				\
    									\
    if (!func)								\
      func = (RET_TYPE (*)ARGS_PROTO)dlsym(RTLD_NEXT, #FUNC);		\
    return (func ARGS_PARAM);						\
  }									\
  RET_TYPE	FUNC ARGS_PROTO						\
  {									\
    _xmalloc_initptr();							\
    return (_xm_real_ ## FUNC ARGS_PARAM);				\
  }

typedef struct		s_xmalloc
{
  void			*ptr;
  char			*type;
  size_t		size;
  char			*file;
  int			line;
  char			*func;
  struct s_xmalloc	*next;
}			t_xmalloc;

extern void	(*_f_xmalloc_add)(void *, char *, size_t _XM_PROTO);
extern void	(*_f_xmalloc_show)(void);
extern void	(*_f_xmalloc_del)(void * _XM_PROTO);

t_xmalloc		*g_xmalloc = NULL;

REAL(malloc, void *, (size_t size), (size))
REAL(calloc, void *, (size_t number, size_t size), (number, size))
REAL(realloc, void *, (void *ptr, size_t size), (ptr, size))
REAL(reallocf, void *, (void *ptr, size_t size), (ptr, size))

void		_xm_real_free(void *ptr)
{
  static void	(*func)(void *);
  
  if (!func)
    func = (void (*)(void *))dlsym(RTLD_NEXT, "free");
  func(ptr);
  return ;
}

void	free(void *ptr)
{
  _xmalloc_initptr();
  _xm_real_free(ptr);
}

void		_xmalloc_add(void *ptr, char *type, size_t size _XM_PROTO_F)
{
  t_xmalloc	*new;

  new = _xm_real_malloc(sizeof(*new));
  new->ptr = ptr;
  new->size = size;
  new->type = type;
  new->file = file;
  new->line = line;
  new->func = func;
  new->next = g_xmalloc;
  g_xmalloc = new;
  return ;
}

void			_xmalloc_show(void)
{
  t_xmalloc	*tmp;
  int		c;

  c = 0;
  printf("+==================================="
	 "====================================+\n");
  for (tmp = g_xmalloc; tmp; tmp = tmp->next)
    printf("| %03d %-10s(%d) - %p " _XM_PRINTF "\r\t\t\t\t\t\t\t\t\t|\n",
	   ++c, tmp->type, tmp->size, tmp->ptr,
	   tmp->file, tmp->line, tmp->func);
  printf("+==================================="
	 "====================================+\n"
	 "Unfreed mallocs: %d\n", c);
  return; 
}

void		_xmalloc_del(void *ptr _XM_PROTO_F)
{
  t_xmalloc	*tmp;
  t_xmalloc	*tmp2;

  if (ptr == NULL)
    return ;
  if (g_xmalloc->ptr == ptr)
    {
      tmp2 = g_xmalloc;
      g_xmalloc = tmp2->next;
      _xm_real_free(tmp2);
      return ;
    }
  else
    for (tmp = g_xmalloc; tmp; tmp = tmp->next)
      if (tmp->next && tmp->next->ptr == ptr)
	{
	  tmp2 = tmp->next;
	  tmp->next = tmp->next->next;
	  _xm_real_free(tmp2);
	  return ;
	}
  printf("chunk is already free - %p " _XM_PRINTF "\n", ptr);
  return ;
}

void	_xmalloc_atexit(void)
{
  _xmalloc_show();
}

int		_xmalloc_initptr(void)
{
  static int	inited = 0;

  if (!inited)
    {
      inited = 1;
      atexit(_xmalloc_atexit);
      _f_xmalloc_add = _xmalloc_add;
      _f_xmalloc_show = _xmalloc_show;
      _f_xmalloc_del = _xmalloc_del;
    }
  return (0);
}
