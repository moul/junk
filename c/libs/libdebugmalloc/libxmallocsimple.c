/**
 * libxmallocsimple.c
 *
 * Copyright (c) Manfred Touron 2008x
 */

#include <sys/types.h>
#include <stdio.h>
#include <dlfcn.h>

void		_xmalloc_add(void *ptr, char *type, size_t size);
void		_xmalloc_del(void *ptr);

#define REAL(FUNC, RET_TYPE, ARGS_PROTO, ARGS_PARAM, ACTION)		\
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
    RET_TYPE	ret;							\
    _xmalloc_initptr();							\
    ret = _xm_real_ ## FUNC ARGS_PARAM;					\
    _xmalloc_add(ret, #FUNC, size);					\
    ACTION;								\
    return (ret);							\
  }

#define _XM_DEL(PTR)	_xmalloc_del(PTR)

REAL(malloc, void *, (size_t size), (size),0)
REAL(calloc, void *, (size_t number, size_t size), (number, size),0)
REAL(realloc, void *, (void *ptr, size_t size), (ptr, size),
     _XM_DEL(ptr))
REAL(reallocf, void *, (void *ptr, size_t size), (ptr, size),
     _XM_DEL(ptr))

typedef struct		s_xmalloc
{
  void			*ptr;
  char			*type;
  size_t		size;
  struct s_xmalloc	*next;
}			t_xmalloc;

t_xmalloc		*g_xmalloc = NULL;

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
  _xmalloc_del(ptr);
}

void		_xmalloc_add(void *ptr, char *type, size_t size)
{
  t_xmalloc	*new;

  new = _xm_real_malloc(sizeof(*new));
  new->ptr = ptr;
  new->size = size;
  new->type = type;
  new->next = g_xmalloc;
  g_xmalloc = new;
  return ;
}

void		_xmalloc_del(void *ptr)
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
  printf("chunk is already free - %p\n", ptr);
  return ;
}

void			_xmalloc_show(void)
{
  t_xmalloc	*tmp;
  int		c;

  printf("+=======================================+\n");
  for (tmp = g_xmalloc; tmp; tmp = tmp->next)
    printf("| %03d %-10s(%d) - %p\r\t\t\t\t\t|\n",
	   ++c, tmp->type, tmp->size, tmp->ptr);
  printf("+=======================================+\n"
	 "Unfreed Mallocs: %d\n", c);
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
    }
  return (0);
}
