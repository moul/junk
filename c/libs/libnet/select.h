/**
 * libnet/net.h
 *
 * Copyright (c) Manfred Touron 2008
 */

#ifndef LIBNET_SELECT_H
# define LIBNET_SELECT_H

# include <liblc/lc.h>

# include "common.h"

int	libnet_select(void);
void	libnet_select_reset(void);
bool	libnet_select_add_fd(int);
bool	libnet_select_del_fd(int);
void	libnet_select_settimeout(int, int);
bool	libnet_select_isset(int);

bool	libnet_select_add_wrfd(int);
bool	libnet_select_del_wrfd(int);

bool	libnet_select_isset_rd(int);
bool	libnet_select_isset_wr(int);

extern lc	_libnet_select_lc;

#define libnet_select_foreach_fd(TMP)			\
  for (lc _tmp_lc = _libnet_select_lc->root;		\
       _tmp_lc && ((void *)TMP = _tmp_lc->ptr || 1);	\
       _tmp_lc = _tmp_lc->next)

#endif /* !LIBNET_SELECT_H */
