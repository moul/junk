/**
 * libnet/select.c
 *
 * Copyright (c) Manfred Touron 2008
 */

#include <stdio.h>
#include <errno.h>
#include <netdb.h>
#include <stddef.h>
#include <string.h>
#include <sys/select.h>

#include <liblc/lc.h>

#include "core.h"
#include "select.h"

lc			_libnet_select_lc = NULL;
lc			_libnet_select_wrlc = NULL;
int			_libnet_select_nfds = 0;
fd_set			_libnet_select_rdfs;
fd_set			_libnet_select_wrfs;
fd_set			_libnet_select_exfs;
struct timeval		_libnet_select_timeout = {0, 0};

extern void		(*_libnet_delete_fd_fn)(int);
void			_libnet_delete_fd(int);

void		_libnet_select_init(void)
{
  static bool	inited = FALSE;

  if (!inited)
    {
      DEBUG_ASCII_IN;
      FD_ZERO(&_libnet_select_rdfs);
      FD_ZERO(&_libnet_select_wrfs);
      FD_ZERO(&_libnet_select_exfs);
      _libnet_select_lc = lc_new();
      _libnet_select_wrlc = lc_new();
      _libnet_delete_fd_fn = _libnet_delete_fd;
      DEBUG_ASCII_OUT;
      inited = TRUE;
    }
  return ;
}

void	_libnet_delete_fd(int fd)
{
  DEBUG_ASCII_IN;
  libnet_select_del_fd(fd);
  RETURN_VOID;
}

int	libnet_select(void)
{
  int	ret;
  int	*tmp;

  DEBUG_ASCII_IN;
  _libnet_select_init();
  _libnet_select_nfds = -1;
  FD_ZERO(&_libnet_select_rdfs);
  FD_ZERO(&_libnet_select_wrfs);
  FD_ZERO(&_libnet_select_exfs);
  lc_foreach(_libnet_select_lc, tmp)
    {
      FD_SET((int)tmp, &_libnet_select_rdfs);
      if ((int)tmp > _libnet_select_nfds)
	_libnet_select_nfds = (int)tmp;
    }
  lc_foreach(_libnet_select_wrlc, tmp)
    {
      FD_SET((int)tmp, &_libnet_select_wrfs);
      if ((int)tmp > _libnet_select_nfds)
	_libnet_select_nfds = (int)tmp;
    }
  if ((ret = select(_libnet_select_nfds + 1, &_libnet_select_rdfs,
		    &_libnet_select_wrfs, &_libnet_select_exfs,
		    _libnet_select_timeout.tv_sec ||
		    _libnet_select_timeout.tv_usec ?
		    &_libnet_select_timeout : NULL)) < 0 &&
      errno != EINTR)
    {
      perror("select");
      RETURN (-1);
    }
  RETURN (ret);
}

bool	libnet_select_isset(int fd)
{
  DEBUG_ASCII_IN;
  RETURN ((bool)(FD_ISSET(fd, &_libnet_select_rdfs) ||
		 FD_ISSET(fd, &_libnet_select_wrfs)));
}

bool	libnet_select_isset_rd(int fd)
{
  DEBUG_ASCII_IN;
  RETURN ((bool)(FD_ISSET(fd, &_libnet_select_rdfs)));
}

bool	libnet_select_isset_wr(int fd)
{
  DEBUG_ASCII_IN;
  RETURN ((bool)FD_ISSET(fd, &_libnet_select_wrfs));
}

void	libnet_select_settimeout(int sec, int usec)
{
  DEBUG_ASCII_IN;
  _libnet_select_timeout.tv_sec = sec;
  _libnet_select_timeout.tv_usec = usec;
  RETURN_VOID;
}

void	libnet_select_reset(void)
{
  DEBUG_ASCII_IN;
  _libnet_select_init();
  _libnet_select_nfds = 0;
  RETURN_VOID;
}

bool	libnet_select_del_fd(int fd)
{
  DEBUG_ASCII_IN;
  _libnet_select_init();
  lc_remove_ptr(_libnet_select_lc, (void *)fd);
  RETURN (TRUE);
}

bool	libnet_select_add_fd(int fd)
{
  DEBUG_ASCII_IN;
  _libnet_select_init();
  lc_push(_libnet_select_lc, (void *)fd);
  RETURN (TRUE);
}

bool	libnet_select_del_wrfd(int fd)
{
  DEBUG_ASCII_IN;
  _libnet_select_init();
  lc_remove_ptr(_libnet_select_wrlc, (void *)fd);
  RETURN (TRUE);
}

bool	libnet_select_add_wrfd(int fd)
{
  DEBUG_ASCII_IN;
  _libnet_select_init();
  lc_push(_libnet_select_wrlc, (void *)fd);
  RETURN (TRUE);
}
