/**
 * libgetopt/getopt.c
 *
 * Copyright (c) Manfred Touron 2008
 */

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

#include "core.h"

int	_getopt_ac = 0;
char **	_getopt_av = NULL;

# define ARG_ISOPT(X)	(X < _getopt_ac && _getopt_av[X][0] == '-' &&	\
			 _getopt_av[X][1] && !_getopt_av[X][2])

void	usage(const char *str)
{
  fprintf(stdout, "usage: %s %s\n", _getopt_av[0], str);
}

int	getopt_init(int ac, char **av)
{
  int	i;

  _getopt_ac = ac;
  _getopt_av = av;
  for (i = 1; i < ac && av[i]; i++)
    ;
  return (i == ac && !av[i]);
}

int	getopt_exists(const char c)
{
  int	i;

  for (i = 1; i < _getopt_ac; i++)
    if (ARG_ISOPT(i) && _getopt_av[i][1] == c)
      return (i);
  return (0);
}

int	getopt_exists_all(const char *fmt)
{
  int	i;
  int	p;

  for (i = 0; fmt[i]; i++)
    if ((p = getopt_exists(fmt[i])))
      {
	if (fmt[i + 1] == ':')
	  {
	    if (p + 1 == _getopt_ac)
	      return (0);
	    i++;
	  }
      }
    else
      return (0);
  return (1);
}

int	getopt_check(const char *fmt)
{
  int	i;
  int	tmp;

  for (i = 1; fmt[i]; i++)
    {
      if ((tmp = getopt_exists(fmt[i])) == 0)
	return (0);
      if (fmt[i + 1] == ':')
	if (i++ + 1 >= _getopt_ac)
	  return (0);
    }
  return (1);
}

char	*getopt_get(const char c, const char *def)
{
  if (!getopt_exists(c))
    return ((char *)def);
  return (_getopt_av[getopt_exists(c) + 1]);
}
