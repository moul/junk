/**
 * liblc/liblc.h
 *
 * Copyright (c) Manfred Touron 2008
 */

#ifndef LIBLC_H
# define LIBLC_H

# include <libmlutil/valist.h>

# include <stdarg.h>

# define CLLBCK_ARGS	VARGS_T

# define lc_foreach(LC, TMP)					\
  if (LC)							\
    for (lc_node _lc_node_tmp = LC->root;			\
	 _lc_node_tmp && ((TMP = _lc_node_tmp->ptr) || 1);	\
	 _lc_node_tmp = _lc_node_tmp->next)

typedef struct		s_lc_node
{
  void			*ptr;

  struct s_lc_node	*prev;
  struct s_lc_node	*next;
}			*lc_node;

typedef struct		s_lc
{
  lc_node		root;
}			*lc;

typedef int		cmpfn2v(void *, void *);
typedef int		walkfn(void *);
typedef int		walkfnv(void *, int, va_list);
typedef int		walkfna(void *, CLLBCK_ARGS);

lc	lc_new(void);
lc	lc_push(lc, void *);
lc	lc_pushn(lc, int, ...);
int	lc_length(lc);
void	lc_debug(lc);
int	lc_walk(lc, walkfn);
int	lc_walk_v(lc, walkfnv, int, va_list);
int	lc_remove(lc, lc_node);
lc	lc_unshift(lc, void *);
lc	lc_unshiftn(lc, int, ...);
void	lc_unset(lc);
void	lc_node_unset(lc, lc_node);
int	lc_remove_ptr(lc, void *);
int	lc_remove_nolimit(lc, lc_node);
int	lc_remove_ptr_nolimit(lc, void *);
void	*lc_find_cmpfn(lc, void *, cmpfn2v);
int	lc_walk_a(lc, walkfna, CLLBCK_ARGS);

/* not yet implemented, ask moul when needed */
lc	lc_merge(lc, lc);
lc	lc_reverse(lc);
lc	lc_sort(lc, int (*)(lc, lc));
void	*lc_shift(lc);
void	*lc_pop(lc);
void	*lc_rand(lc);
void	lc_reduce(lc, void (*)(lc));

#endif /* !LIBLC_H */
