/**
 * libwebsite/url.c
 *
 * Copyright (c) Manfred Touron 2008
 */

#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

#include "core.h"
#include "environ.h"
#include "url.h"

char	*trim_url(char *str)
{
  int	i;
  int	j;
  char	in;

  while (*str && *str == '/')
    str++;
  j = 0;
  in = 1;
  for (i = 0; str[i]; i++)
    if (!in)
      {
	if (str[i] == '/' && str[i + 1] && str[i + 1] == '/')
	  in = 1;
	str[j++] = str[i];
      }
    else if (str[i] != '/')
      {
	str[j++] = str[i];
	in = 0;
      }
  if (str[j - 1] == '/')
    str[j - 1] = 0;
  else
    str[j] = 0;
  return (str);
}

char		*arg(int pos)
{
  static char	**getq = NULL;
  static int	length = 0;
  int		i;
  char		*tmp;

  if (getq == NULL)
    {
      tmp = GETENV(REQUEST_URI);
      if (!tmp)
	return (NULL);
      getq = ALLOC_N(char *, 1024);
      getq[0] = strdup(tmp);
      if (getq[0][0])
	{
	  getq[0] = trim_url(getq[0]);
	  if (getq[0][0] == '/')
	    getq[0]++;
	  length = 1;
	  for (i = 0; i < getq[0][i]; i++)
	    if (getq[0][i] == '/')
	      {
		getq[0][i] = 0;
		if (getq[0][i + 1])
		  getq[length++] = getq[0] + i + 1;
	      }
	  getq[length] = NULL;
	}
    }
  return (pos < length ? getq[pos] : NULL);
}
