/**
 * libwebsite/header.c
 *
 * Copyright (c) Manfred Touron 2008
 */

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

#include <liblc/lc.h>

#include "core.h"

lc	_header_list = NULL;

int	ws_add_header(char *str)
{
  if (_header_list == NULL)
    _header_list = lc_new();
  lc_push(_header_list, str);
  return (1);
}

int	_ws_print_headers(void *header)
{
  printf(header);
  printf("\r\n");
}

int	ws_print_headers(void)
{
  if (_header_list)
    lc_walk(_header_list, _ws_print_headers);
  printf("\r\n");
  return (1);
}
