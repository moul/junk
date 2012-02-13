/**
 * mgs/routine.c
 * 
 * Copyright (c) Manfred Touron 2008
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>

#include "server.h"

void			routine(t_mgs_context *ctx)
{
  int			max;
  fd_set		rfds;
  fd_set		wfds;
  struct timeval	timeout;
  int			nb;

  timeout.tv_sec = 0;
  timeout.tv_usec = 0;
  while (42)
    {
      mgs_api_callback(MGS_CALLBACK_TIMEOUT, (void *)&timeout, (void *)0);
      max = init_mgs_fdset(&rfds, &wfds, ctx);
      nb = select(max + 1, &rfds, &wfds, NULL,
		  (timeout.tv_usec || timeout.tv_sec ? &timeout : NULL));
      if (nb < 0)
	{
	  if (errno == EINTR)
	    continue ;
	  perror("select");
	  exit(1);
	}
      else if (nb)
	{
	  check_fdset(&rfds, &wfds, ctx);
	  net_mgs_traitement(ctx);
	}
      else
	mgs_api_callback(MGS_CALLBACK_SELECT_ON_TIMEOUT, ctx, (void *)0);
      mgs_api_callback(MGS_CALLBACK_SELECT_ALL, ctx, (void *)0);
    }
}

void		net_mgs_traitement(t_mgs_context *context)
{
  char		*line;
  t_mgs_client	*tmp;

  tmp = context->clients;
  while (tmp)
    {
      if (tmp->sizein > 0)
	while ((line = get_buffin_next_line(tmp)))
	  {
	    parser(tmp, line);
	    if (tmp->tmpbuf)
	      {
		free(tmp->tmpbuf);
		tmp->tmpbuf = NULL;
	      }
	  }
      tmp = tmp->next;
    }
  mgs_api_callback(MGS_CALLBACK_SELECT_ON_FDCHANGE, context, (void *)0);
  return ;
}
