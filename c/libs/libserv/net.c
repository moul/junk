/**
 * mgs/net.c
 * 
 * Copyright (c) Manfred Touron 2008
 */

#include <arpa/inet.h>
#include <errno.h>
#include <fcntl.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/filio.h>
#include <sys/ioctl.h>
#include <sys/select.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sysexits.h>
#include <unistd.h>

#include "server.h"

void	mgs_tunneling_line(t_mgs_client *client, char *line, int debug)
{
  char	*tmp;
  int	size;

  size = strlen(line);
  tmp = (char *)xmalloc(client->sizeout + size);
  if (debug)
    VERBOSE(printf("\033[%dm[%03d] > %s\033[m",
		   COLOR(client->fd), client->fd, line));
  if (client->sizeout > 0)
    {
      memcpy(tmp, client->buffout, client->sizeout);
      free(client->buffout);
    }
  memcpy(tmp + client->sizeout, line, size);
  client->buffout = tmp;
  client->sizeout += size;
  return ;
}

void			accept_mgs_new_client(t_mgs_context *context)
{
  struct sockaddr_in	in;
  int			fd;
  int			size;

  size = sizeof(in);
  if ((fd = accept(context->fd, (struct sockaddr *)&in,
		   (socklen_t *)&size)) == -1)
    {
      perror("accept");
      exit(1);
    }
  VERBOSE(printf("\033[%dm[%03d] - Connection from %s\033[m\n",
		 COLOR(fd), fd, inet_ntoa(in.sin_addr)));
  client_add(context, fd);
  return ;
}

void		write_to_client(t_mgs_client *client)
{
  int		ret;
  char		*buf;

  ret = write(client->fd, client->buffout, client->sizeout);
  if (ret < 0)
    {
      client_delete(client);
      return ;
    }
  if (ret < client->sizeout)
    {
      buf = (char *)xmalloc(client->sizeout - ret);
      memcpy(buf, client->buffout + ret, client->sizeout - ret);
      free(client->buffout);
      client->buffout = buf;
      client->sizeout -= ret;
    }
  else
    {
      free(client->buffout);
      client->sizeout = 0;
      client->buffout = NULL;
    }
  return ;
}

int			create_tcp_server(int port)
{
  struct sockaddr_in	server_sock;
  int			server_fd;
  int			opt;
  struct protoent	*pe;

  pe = getprotobyname("tcp");
  server_fd = xsocket(pe);
  opt = 1;
  setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR,
	     (void *)&opt, sizeof(opt));
  server_sock.sin_family = AF_INET;
  server_sock.sin_addr.s_addr = INADDR_ANY;
  if (!port)
    return (-1);
  server_sock.sin_port = htons(port);
  if ((xbind(server_fd, (struct sockaddr *)&server_sock)) < 0
      || xlisten(server_fd) < 0)
    return (-1);
  return (server_fd);
}
