/**
 * libnet/net.c
 *
 * Copyright (c) Manfred Touron 2008
 */

#include <stdio.h>
#include <netdb.h>
#include <stddef.h>
#include <string.h>
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

#include <libmlutil/misc.h>

#include "core.h"
#include "net.h"

void		(*_libnet_delete_fd_fn)(int) = NULL;

bool	libnet_init(void)
{
  return (TRUE);
}

void	libnet_uninit(void)
{
  return;
}

int	libnet_close(int fd)
{
  int	ret;

  DEBUG_ASCII_IN;
  if (_libnet_delete_fd_fn)
    _libnet_delete_fd_fn(fd);
  if ((ret = close(fd)) < 0)
    {
      perror("close");
      RETURN (-1);
    }
  RETURN (ret);
}

int	libnet_write(int fd, char *buf, int size)
{
  int	ret;

  DEBUG_ASCII_IN;
  if ((ret = write(fd, buf, size)) < 0)
    {
      perror("write");
      RETURN (-1);
    }
  RETURN (ret);
}

int	libnet_send(int fd, char *buf)
{
  int	ret;

  printf("\033[%dm[%03d] ---> %s\033[m", DCOL(fd), fd, buf);
  DEBUG_ASCII_IN;
  if ((ret = send(fd, buf, strlen(buf), 0)) < 0)
    {
      perror("send");
      RETURN (-1);
    }
  RETURN (ret);
}

int	libnet_sendudp(int fd, struct sockaddr_in *saddr, char *buf)
{
  int	ret;

  printf("[UDP] ---> %s", buf);
  DEBUG_ASCII_IN;
  if ((ret = sendto(fd, buf, strlen(buf), 0, (struct sockaddr *)saddr,
		    sizeof(*saddr))) < 0)
    {
      perror("sendto");
      RETURN (-1);
    }
  RETURN (ret);
}

int		libnet_printfudp(int fd, struct sockaddr_in *saddr,
			      const char *fmt, ...)
{
  va_list	varg;
  int		ret;

  DEBUG_ASCII_IN;
  va_start(varg, fmt);
  ret = libnet_vprintfudp(fd, saddr, fmt, varg);
  va_end(varg);
  RETURN (ret);
}

int		libnet_vprintfudp(int fd, struct sockaddr_in *saddr,
			       const char *fmt, va_list varg)
{
  int		ret;
  static char	*buf = NULL;

  DEBUG_ASCII_IN;
  ret = vfprintf(fopen("/dev/null", "w"), fmt, varg) + 1;
  buf = REALLOC_N(buf, char, 0, ret + 1);
  vsnprintf(buf, ret, fmt, varg);
  ret = libnet_sendudp(fd, saddr, buf);
  RETURN (ret);
}

int		libnet_printf(int fd, const char *fmt, ...)
{
  va_list	varg;
  int		ret;

  DEBUG_ASCII_IN;
  va_start(varg, fmt);
  ret = libnet_vprintf(fd, fmt, varg);
  va_end(varg);
  RETURN (ret);
}

int		libnet_vprintf(int fd, const char *fmt, va_list varg)
{
  int		ret;
  static char	*buf = NULL;

  DEBUG_ASCII_IN;
  ret = vfprintf(fopen("/dev/null", "w"), fmt, varg) + 1;
  buf = REALLOC_N(buf, char, 0, ret + 1);
  vsnprintf(buf, ret, fmt, varg);
  ret = libnet_send(fd, buf);
  RETURN (ret);
}


int	libnet_sendline(int fd, char *buf)
{
  int	ret;

  DEBUG_ASCII_IN;
  if ((ret = send(fd, buf, strchr(buf, '\n') - buf + 1, 0)) < 0)
    {
      perror("send");
      RETURN (-1);
    }
  RETURN (ret);
}

int	libnet_read(int fd, char *buf, int size)
{
  int	ret;

  DEBUG_ASCII_IN;
  if ((ret = read(fd, buf, size)) < 0)
    {
      perror("read");
      RETURN (-1);
    }
  RETURN (ret);
}

int	libnet_rbufread(int fd, rbuf buf)
{
  int	ret;

  DEBUG_ASCII_IN;
  ret = rbuf_read(fd, buf, 1024);
  RETURN (ret);
}

rbuf	libnet_rbufget(int fd)
{
  rbuf	buf;

  DEBUG_ASCII_IN;
  buf = rbuf_new(0);
  rbuf_read(fd, buf, 1024);
  RETURN (buf);
}
