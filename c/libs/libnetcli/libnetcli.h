/**
 * libnetcli/libnetcli.h
 *
 * Copyright (c) Manfred Touron 2008
 */

#ifndef LIBNETCLI_H
# define LIBNETCLI_H

# include <libmlutil/valist.h>

# define METHOD_PTR(NAME, ARGS)	(*NAME)ARGS
# define MPA			struct s_lnc *

typedef void	slctcllbckfn(void *, VARGS_T);

# define SELECT_CALLBACK(NAME)	void NAME(void *lnc, VARGS_T argv)

typedef struct	s_lnc
{
  void		*v;

  int		METHOD_PTR(unset, (MPA));
  int		METHOD_PTR(send, (MPA, char *));
  int		METHOD_PTR(read, (MPA, char *, int));
  int		METHOD_PTR(connected, (MPA));
  int		METHOD_PTR(fd, (MPA));
  int		METHOD_PTR(select_type, (MPA, const char *));
  int		METHOD_PTR(select_type_add_callback, (MPA, const char *,
						      slctcllbckfn));
}		*lnc;

lnc		lnc_connect(char *, int);

#endif /* !LIBNETCLI_H */
