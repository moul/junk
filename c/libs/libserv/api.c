/**
 * mgs/api.c
 * 
 * Copyright (c) Manfred Touron 2008
 */

#include <stdlib.h>
#include <stdio.h>

#include "server.h"

#ifdef PRELOAD_MODULES
#include <dlfcn.h>
void	api_init(t_mgs_context *context)
{
  if (!(dlopen(XSTR(MODULE_NAME), RTLD_NOW)))
    {
      printf("dlopen("XSTR(MODULE_NAME)"): %s\n", dlerror());
      exit(-1);
    }
  (void)context;
}
#else /* PRELOAD_MODULES */
extern int	_init(void);

void	api_init(t_mgs_context *context)
{
  (void)context;
  /*_init();*/
}
#endif /* !PRELOAD_MODULES */

t_mgs_cmd		*mgs_api_cmd_callbacks(t_mgs_cmd *from)
{
  static t_mgs_cmd	*cache = 0;

  if (from)
    cache = from;
  return (cache);
}

t_mgs_callback		*mgs_api_callbacks(t_mgs_callback *from)
{
  static t_mgs_callback	*cache = 0;

  if (from)
    cache = from;
  return (cache);
}

int			mgs_api_callback(int id, void *param, void *param2)
{
  t_mgs_callback	*callbacks;

  callbacks = mgs_api_callbacks((void *)0);
  if (callbacks && callbacks[id].func)
    return (callbacks[id].func(param, param2));
  return (0);
}
