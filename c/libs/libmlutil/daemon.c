/**
 * libmlutil/daemon.c
 *
 * Copyright (c) Manfred Touron 2008
 */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>

#include "daemon.h"

bool	mu_daemon(int nochdir, int noclose)
{
  int	fd;

  switch (fork())
    {
    case -1:
      perror("fork");
      return (FALSE);
    case 0:
      break;
    default:
      exit (0);
    }
  if (setsid() == -1)
    {
      perror("setsid");
      return (FALSE);
    }
  if (!nochdir)
    (void)chdir("/");
  if (!noclose && (fd = open("/dev/null", O_RDWR, 0)) > -1)
    {
      (void)dup2(fd, STDIN_FILENO);
      (void)dup2(fd, STDOUT_FILENO);
      (void)dup2(fd, STDERR_FILENO);
      if (fd > 2)
	(void)close(fd);
    }
  return (TRUE);
}
