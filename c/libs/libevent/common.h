/**
 * libevent/common.h
 *
 * Copyright (c) Manfred Touron 2008
 */

#ifndef LIBEVENT_COMMON_H
# define LIBEVENT_COMMON_H

# include <liblc/lc.h>

# include <libmlutil/valist.h>

# include "types.h"

typedef struct	s_event
{
  const char	*name;
  lc		lc;
}		*event;

typedef int	cllbck(void **);

#endif /* !LIBEVENT_COMMON_H */
