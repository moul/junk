/**
 * mgs/buffer.c
 * 
 * Copyright (c) Manfred Touron 2008
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "server.h"

char		*get_splitted_buffin_next_line(t_mgs_client *client)
{
  int		i;

  client->tmpbuf = xmalloc(sizeof(*client->tmpbuf) * (BUF_SIZE + 1));
  memcpy(client->tmpbuf, client->buffin + client->offin, BUF_SIZE - client->offin);
  i = 0;
  while (client->buffin[i] != '\n')
    {
      if (i >= BUF_SIZE)
	return (NULL);
      i++;
    }
  client->buffin[i] = 0;
  memcpy(client->tmpbuf + BUF_SIZE - client->offin, client->buffin, i + 1);
  client->sizein -= (BUF_SIZE - client->offin + i + 1);
  client->offin = i + 1;
  return (client->tmpbuf);
}

char		*get_buffin_next_line(t_mgs_client *client)
{
  char		*line;
  int		i;

  if (!client->sizein)
    return (NULL);
  line = client->buffin;
  i = client->offin;
  while (i < client->offin + client->sizein)
    {
      if (i >= BUF_SIZE)
	return (get_splitted_buffin_next_line(client));
      if (!line[i])
	return (NULL);
      if (line[i] == '\n')
	{
	  line[i] = 0;
	  line += client->offin;
	  client->sizein -= (i - client->offin + 1);
	  client->offin += (i - client->offin + 1);
	  break;
	}
      i++;
    }
  return (line);
}

int		check_read_from_client(t_mgs_client *client, int *size)
{
  if (xioctl(client, client, size))
    return (1);
  if (client->sizein + *size >= BUF_SIZE)
    {
      printf("too long message\n");
      exit(0);
    }
  if (*size == 0)
    {
      client_delete(client);
      return (1);
    }
  return (0);
}

int		read_from_client(t_mgs_client *client)
{
  int		size;
  int		tmp;

  if (check_read_from_client(client, &size))
    return (1);
  tmp = size;
  if (client->offin + client->sizein + size >= BUF_SIZE)
    tmp = BUF_SIZE - (client->offin + client->sizein);
  if (read(client->fd, client->buffin + client->sizein + client->offin,
	   tmp) < 0 || (tmp != size && read(client->fd, client->buffin,
					    size - tmp) < 0))
    {
      client_delete(client);
      return (1);
    }
  client->sizein += size;
  return (0);
}
