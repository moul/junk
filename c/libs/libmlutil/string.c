/**
 * libmlutil/string.c
 *
 * Copyright (c) Manfred Touron 2008
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "string.h"
#include "misc.h"

int		mu_strcmp(void *a, void *b)
{
  return (strcmp((a ? a : ""), (b ? b : "")));
}

int		vprintflen(char *fmt, va_list varg)
{
  static FILE	*fd_dev_null = NULL;

  if (fd_dev_null == NULL)
    fd_dev_null = fopen("/dev/null", "w");
  return (vfprintf(fd_dev_null, (const char *)fmt, varg) + 1);
}

int		printflen(char *fmt, ...)
{
  va_list	varg;
  int		ret;

  va_start(varg, fmt);
  ret = vprintflen(fmt, varg);
  va_end(varg);
  return (ret);
}

char		*addslashes(char *from)
{
  static char	*new = NULL;
  int		i;
  int		j;

  j = 0;
  for (i = 0; from[i]; i++)
    {
      if (from[i] == '"' || from[i] == '\\')
	j++;
      j++;
    }
  new = REALLOC_N(new, char, 0, j);
  j = 0;
  for (i = 0; from[i]; i++)
    {
      if (from[i] == '"' || from[i] == '\\')
	new[i + j++] = '\\';
      new[i + j] = from[i];
    }
  return (new);
}

char	*stripslashes(char *from)
{
  int	i;
  int	j;
  int	size;

  size = strlen(from);
  j = 0;
  for (i = 0; i < size; i++)
    {
      if (from[i + j] == '\\')
	j++;
      from[i] = from[i + j];
    }
  return (from);
}

int	wordtablength(char **tab)
{
  int	i;

  for (i = 0; tab[i] != NULL; i++)
    ;
  return (i);
}

char		**strtowordtab(char *from, char delim, char protector)
{
  int		i;
  static char	*tab[MAX_WORDS];
  int		j;
  int		protected;
  int		isword;

  protected = 0;
  j = 0;
  for (i = 0; from[i]; i++)
    {
      if (from[i] == protector)
	protected = 1 - protected;
      if (!protected && from[i] == delim)
	j++;
    }
  /*tab = REALLOC_N(tab, char *, 0, j + 1);*/
  j = 0;
  protected = 0;
  isword = 0;
  for (i = 0; from[i]; i++)
    {
      if ((!protected && from[i] == delim) ||
	  (protected && from[i] == protector &&
	   (!i || from[i - 1] != '\\')))
	{
	  isword = 0;
	  from[i] = 0;
	  if (protected)
	    tab[j - 1] = stripslashes(tab[j - 1]);
	  protected = 0;
	}
      else if (from[i] == protector)
	protected = 1 - protected;
      else if (!isword && from[i] != delim && from[i] != protector)
	{
	  tab[j++] = from + i;
	  isword = 1;
	}
      /*printf("char: %c, isword: %d, protected: %d\n",
	from[i], isword, protected);*/
    }
  tab[j] = NULL;
  return (tab);
}
