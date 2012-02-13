/**
 * libnetcli/libnetcli.h
 *
 * Copyright (c) Manfred Touron 2008
 */

#ifndef LIBNETCLI_CORE_H
# define LIBNETCLI_CORE_H

# include <sys/types.h>
# include <sys/socket.h>
# include <netinet/in.h>
# include <arpa/inet.h>

# include "libnetcli.h"
# include "select.h"

# define t_connect		lnc_connection

# define METHOD(NAME, ARGS)	METHOD_NAME(NAME) ARGS
# define METHOD_NAME(NAME)	lnc_m_ ## NAME
# define METHOD_ADD(NAME)	lnc->NAME = METHOD_NAME(NAME)
# define METHOD_ARGS		lnc this

# define V(X)			((lnc_v)((X)->v))
# define THIS			(V(this))

typedef struct
{
  char			*hostname;
  int			port;

  struct hostent	*he;
  struct sockaddr_in    sin;
  struct protoent       *pe;

  int			connected;
  int			fd;

  select_link		select;
}			*lnc_v;

lnc	lnc_new(void);
int	METHOD(unset, (METHOD_ARGS));
int	METHOD(send, (METHOD_ARGS, char *));
int	METHOD(read, (METHOD_ARGS, char *, int));
int	METHOD(connected, (METHOD_ARGS));
int	METHOD(fd, (METHOD_ARGS));
int	METHOD(select_type, (METHOD_ARGS, const char *));
int	METHOD(select_type_add_callback,
	       (METHOD_ARGS, const char *, slctcllbckfn));

#endif /* !LIBNETCLI_CORE_H */
