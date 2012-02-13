/**
 * libnetcli/select.c
 *
 * Copyright (c) Manfred Touron 2008
 */

#include <sys/ioctl.h>
#include <stdio.h>
#include <netdb.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>

#include <liblc/lc.h>

#include <libmlutil/debug.h>

#include "core.h"
#include "select.h"

slct	select_new(void)
{
  slct	new;

  if ((new = ALLOC(*new)) == NULL)
    perror("malloc");
  new->timeout = INFTIM;
  new->count = 0;
  return (new);
}

int	lnc_select(slct select)
{
  return (poll(select->pfds, select->count, select->timeout));
}

void	lnc_select_clean(slct select)
{
  int	i;

  for (i = 0; i < select->count; i++)
    {
      select->pfds[i].revents = 0;
      select->pfds[i].events = POLLIN;
    }
  return ;
}

int	lnc_select_loop(slct select)
{
  int	ret;

  while (select->count)
    {
      ret = lnc_select(select);
      lnc_select_call_callbacks(select);
      lnc_select_clean(select);
    }
  return (0);
}

void	select_add_fd(slct select, int fd)
{
  select->pfds[select->count].fd = fd;
  select->pfds[select->count].events = POLLIN;
  select->pfds[select->count].revents = 0;
  select->count++;
  return ;
}

int		lnc_select_size_to_read(int fd)
{
  int		size;

  if ((ioctl(fd, FIONREAD, &size)) < 0)
    perror("ioctl");
  return (size);
}

void		lnc_select_call_callbacks(slct select)
{
  int		i;
  select_link	link;
  int		size;

  for (i = 0; i < select->count; i++)
    if (select->pfds[i].revents & POLLIN)
      {
	link = lnc_select_link_find_by_fd(select->pfds[i].fd);
	size = lnc_select_size_to_read(select->pfds[i].fd);
	rbuf_read(select->pfds[i].fd, link->rbuf, size);
	write(1, ".", 1);
      }
  exit(0);
  return ;
}
