/**
 * libevent/libevent.h
 *
 * Copyright (c) Manfred Touron 2008
 */

#ifndef LIBEVENT_H
# define LIBEVENT_H

# include <stdarg.h>
# include <string.h>

# include <libmlutil/valist.h>

# include "common.h"

extern event	event_new(const char *);
extern void	event_debug(const char *);
extern void	events_debug(void);
extern int	event_e_debug(void *);
extern event	event_find(const char *);
extern int	event_callback_exists(event, cllbck);
extern int	event_call(const char *, CLLBCK_ARGS);

#endif /* !LIBEVENT_H */
