/**
 * libservices/net.h
 *
 * Copyright (c) Manfred Touron 2008
 */

#ifndef LIBSERVICES_NET_H
# define LIBSERVICES_NET_H

# include "common.h"
# include "client.h"

typedef struct
{
  char		*hostname;
  int		port;
  char		*login;
  char		*password;

  struct
  {
    int		fd;
  }		internal;
}		srvc_server;

# define SS_NET_ARGS	net_services, 

/* net */
extern net_services	net_services_connect(char *, int, char *, char *);
extern int		net_service_exists(SS_NET_ARGS const char *);
extern void		*net_service_call(SS_NET_ARGS
					  const char *, int, ...);
extern void		net_service_help(SS_NET_ARGS);
extern void		*net_service_getptr(SS_NET_ARGS
					    void *, size_t, size_t);


#endif /* !LIBSERVICES_NET_H */
