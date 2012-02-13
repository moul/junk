/**
 * mgs/api.h
 *
 * Copyright (c) Manfred Touron 2008
 */

#ifndef _MGS_API_H
# define _MGS_API_H

/**
 * includes
 */
# include "timer.h"

/**
 * defines
 */
enum {
  MGS_CALLBACK_CLIENT_ADD,
  MGS_CALLBACK_CLIENT_DEL,
  MGS_CALLBACK_TIMEOUT,
  MGS_CALLBACK_UNKNOWN_COMMAND,
  MGS_CALLBACK_SELECT_ALL,
  MGS_CALLBACK_SELECT_ON_TIMEOUT,
  MGS_CALLBACK_SELECT_ON_FDCHANGE,
  MGS_CALLBACK_USAGE
};

# define CONTEXT_PTR		mgs_get_context_ptr((t_mgs_context *)0)

/**
 * structures
 */
typedef struct		s_mgs_client
{
  void			*p;
  int			flag;
  int			id;

  int			noread;
  int			fd;

  char			*buffin;
  int			sizein;
  int			offin;
  int			offinend;

  char			*buffout;
  int			sizeout;
  int			offout;
  int			offoutend;

  char			*tmpbuf;

  struct s_mgs_client	*next;
}			t_mgs_client;

typedef struct		s_mgs_cmd
{
  char			*command;
  int			(*action)(t_mgs_client *, char *);
}			t_mgs_cmd;

typedef struct		s_mgs_callback
{
  int			(*func)(void *, void *);
}			t_mgs_callback;

typedef struct		s_mgs_context
{
  int			fd;
  t_mgs_client		*clients;
}			t_mgs_context;

/**
 * prototypes
 */
t_mgs_cmd		*mgs_api_cmd_callbacks(t_mgs_cmd *);
t_mgs_callback		*mgs_api_callbacks(t_mgs_callback *);
int			mgs_api_callback(int, void *, void *);

void			mgs_tunneling_line(struct s_mgs_client *, char *, int);
t_mgs_context		*mgs_get_context_ptr(t_mgs_context *);
void			client_delete(t_mgs_client *);

#endif /* !_MGS_API_H */
