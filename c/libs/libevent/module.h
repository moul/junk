/**
 * libevent/module.h
 *
 * Copyright (c) Manfred Touron 2008
 */

#ifndef LIBEVENT_MODULE_H
# define LIBEVENT_MODULE_H

# include "common.h"

typedef struct
{
  char			*name;
  int			(*init)(void);
  void			(*uninit)(void);
  int			inited;
}			t_module;

# define EAH_PROTO	const char *, cllbck

/*
extern int	modules_init(t_module *);
extern void	modules_uninit(t_module *);
*/
extern void	event_del_handler(EAH_PROTO);
extern void	event_add_handler(const char *, cllbck);

extern t_module		client_static_modules[];

# define MODULES_INIT()		modules_init(client_static_modules)
# define MODULES_UNINIT()	modules_uninit(client_static_modules)

#endif /* !LIBEVENT_MODULE_H */
