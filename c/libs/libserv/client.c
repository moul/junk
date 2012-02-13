/**
 * mgs/client.c
 * 
 * Copyright (c) Manfred Touron 2008
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "server.h"

t_mgs_client	*client_init_new(int fd)
{
  t_mgs_client	*tmp;
  static int	id = 0;

  tmp = xmalloc(sizeof(*tmp));
  tmp->id = id++;
  tmp->buffin = xmalloc(sizeof(*tmp->buffin) * (BUF_SIZE + 1));
  tmp->buffout = NULL;
  tmp->tmpbuf = NULL;
  tmp->offin = 0;
  tmp->offout = 0;
  tmp->offinend = 0;
  tmp->offoutend = 0;
  tmp->sizein = 0;
  tmp->sizeout = 0;
  tmp->p = (void *)0;
  tmp->fd = fd;
  tmp->next = NULL;
  tmp->noread = 0;
  return (tmp);
}

t_mgs_client	*client_add(t_mgs_context *context, int fd)
{
  t_mgs_client	*tmp;
  t_mgs_client	*tmp_;

  tmp = client_init_new(fd);
  tmp_ = context->clients;
  mgs_api_callback(MGS_CALLBACK_CLIENT_ADD, tmp, (void *)0);
  if (!tmp_)
    {
      context->clients = tmp;
      return (tmp);
    }
  while (tmp_->next)
    tmp_ = tmp_->next;
  tmp_->next = tmp;
  return (tmp);
}

void	client_uninit(t_mgs_client *client)
{
  close(client->fd);
  client->fd = -1;
  free(client->buffin);
  if (client->sizeout)
    free(client->buffout);
  client->buffin = NULL;
  client->buffout = NULL;
  free(client);
  return ;
}

void		client_delete(t_mgs_client *cli)
{
  t_mgs_client	*tmp;
  t_mgs_client	*tmp2;
  t_mgs_context	*context;

  VERBOSE(printf("\033[%dm[%03d] - Disconnected\033[m\n",
		 COLOR(cli->fd), cli->fd));
  mgs_api_callback(MGS_CALLBACK_CLIENT_DEL, cli, (void *)0);
  context = CONTEXT_PTR;
  tmp = context->clients;
  if (tmp->fd == cli->fd)
    {
      context->clients = tmp->next;
      client_uninit(tmp);
      return ;
    }
  tmp2 = context->clients;
  tmp = tmp2->next;
  while (tmp->fd != cli->fd)
    {
      tmp = tmp->next;
      tmp2 = tmp2->next;
    }
  tmp2->next = tmp->next;
  client_uninit(tmp);
}
