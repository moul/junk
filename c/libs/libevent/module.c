/**
 * libevent/core.c
 *
 * Copyright (c) Manfred Touron 2008
 */

#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>

#include "module.h"
#include "core.h"

int	modules_init(t_module *modules)
{
  int	i;
  int	ret;

  ret = 1;
  for (i = 0; modules[i].name; i++)
    ret *= (modules[i].inited = (!!modules[i].init()));
  return (ret);
}

void	modules_uninit(t_module *modules)
{
  int	i;

  for (i = 0; modules[i].name; i++)
    modules[i].uninit();
}
