/**
 * libnetcli/select.h
 *
 * Copyright (c) Manfred Touron 2008
 */

#ifndef LIBNETCLI_SELECT_H
# define LIBNETCLI_SELECT_H

# include <sys/types.h>
# include <sys/socket.h>
# include <netinet/in.h>
# include <arpa/inet.h>
# include <sys/poll.h>

# include <librbuf/librbuf.h>
# include <liblc/lc.h>

# include "libnetcli.h"

# define SELECT_BUF_SIZE	1024

typedef struct
{
  const char		*name;
  void			(*fn)(void *, VARGS_T argv);
}			*slctcllbck;

typedef struct
{
  const char		*name;
  lc			callbacks;
}			*select_type;

typedef struct
{
  select_type		type;
  int			fd;
  lnc			lnc;
  rbuf			rbuf;
}			*select_link;

typedef struct
{
  struct pollfd		pfds[1024];
  int			timeout;
  int			count;
}			*slct;

int		select_type_by_fd(int, const char *);
select_link	select_link_new_by_fd(int);
int		lnc_select_fd_cmpfn(void *, void *);
select_link	lnc_select_link_find_by_fd(int);
int		lnc_select(slct);
int		lnc_select_loop(slct);
void		lnc_select_call_callbacks(slct);
void		select_add_fd(slct, int);
slct		select_new(void);
int		lnc_select_cmpfn(void *, void *);
select_type	lnc_select_type_find(const char *);
select_link	lnc_select_link_find(const char *);
int		lnc_select_type_exists(const char *);
int		lnc_select_link_exists(const char *);
select_type	lnc_select_type_new(const char *);

#endif /* !LIBNETCLI_SELECT_H */
