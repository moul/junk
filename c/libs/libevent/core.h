/**
 * libevent/libevent.h
 *
 * Copyright (c) Manfred Touron 2008
 */

#ifndef LIBEVENT_CORE_H
# define LIBEVENT_CORE_H

# include <stddef.h>

# include "libevent.h"

# define ALLOC(X)		malloc(sizeof(X))
# define ALLOC_N(X, N)		malloc(sizeof(X) * N)

lc	events;

event	events_add(event);
event	events_find(const char *);
int	events_event_exists(event);
int	events_event_cmpfn(void *, void *);
void	event_callback_delete(event, cllbck);
void	event_unset(event);
int	event_call_walk_a(void *, CLLBCK_ARGS);

#endif /* !LIBEVENT_CORE_H */
