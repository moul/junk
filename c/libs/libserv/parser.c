/**
 * mgs/parser.c
 * 
 * Copyright (c) Manfred Touron 2008
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "server.h"

int		first_word_length(char *str)
{
  int		i;

  i = 0;
  while (str[i] && str[i] != ' ' && str[i] != '\n' &&
	 str[i] != '\t' && str[i] != '\r')
    i++;
  return (i);
}

int		parser(t_mgs_client *client, char *line)
{
  int		i;
  t_mgs_cmd	*cmds;

  if (!strlen(line) || line[0] == ' ')
    return (0);
  cmds = mgs_api_cmd_callbacks((void*)0);
  i = -1;
  while (line[++i] && line[i] != ' ')
    if (line[i] >= 'a' && line[i] <= 'z')
      line[i] = line[i] - 'a' + 'A';
  if (line[strlen(line) - 1] == '\r')
    line[strlen(line) - 1] = 0;
  i = -1;
  while (cmds[++i].command != NULL)
    if (!(strncmp(cmds[i].command, line, first_word_length(line))))
      return (cmds[i].action(client, line));
  mgs_api_callback(MGS_CALLBACK_UNKNOWN_COMMAND, client, line);
  return (0);
}
