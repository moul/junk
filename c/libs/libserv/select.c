/**
 * mgs/select.c
 *
 * Copyright (c) Manfred Touron 2008
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

#include "server.h"

int	init_mgs_fdset(fd_set *rfds, fd_set *wfds, t_mgs_context *context)
{
  int		max;
  t_mgs_client	*tmp;

  FD_ZERO(rfds);
  FD_ZERO(wfds);
  max = -1;

  FD_SET(context->fd, rfds);
  if (context->fd > max)
    max = context->fd;
  tmp = context->clients;
  while (tmp)
    {
      if (tmp->fd != -1)
	{
	  if (set_my_fd(tmp, rfds, wfds,
			tmp->noread ? SET_ONLY_WRITE : SET_READ_WRITE)
	      > max)
	    max = tmp->fd;
	}
      tmp = tmp->next;
    }
  return (max);
}

void	check_fdset(fd_set *rfds, fd_set *wfds, t_mgs_context *context)
{
  t_mgs_client	*tmp;

  if (FD_ISSET(context->fd, rfds))
    accept_mgs_new_client(context);
  tmp = context->clients;
  while (tmp)
    {
      if (tmp->fd >= 0)
	{
	  if (FD_ISSET(tmp->fd, rfds))
	    if (read_from_client(tmp))
	      return ;
	  if (tmp->buffout != NULL && FD_ISSET(tmp->fd, wfds))
	    write_to_client(tmp);
	}
      tmp = tmp->next;
    }
  return ;
}

int	set_my_fd(t_mgs_client *client, fd_set *rfds, fd_set *wfds, int flag)
{
  if ((flag & SET_ONLY_READ))
    FD_SET(client->fd, rfds);
  if ((flag & SET_ONLY_WRITE)
      && client->sizeout)
    FD_SET(client->fd, wfds);
  return (client->fd);
}
