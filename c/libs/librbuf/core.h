/**
 * librbuf/librbuf.h
 *
 * Copyright (c) Manfred Touron 2008
 */

#ifndef LIBRBUF_CORE_H
# define LIBRBUF_CORE_H

# include <stddef.h>

# include "librbuf.h"

# define RBUF_SIZE		256
# define CALC_RBUF_SIZE(S)	(((S) / RBUF_SIZE + 1) * RBUF_SIZE)

void	rbuf_realloc_buf(rbuf, int);
void	rbuf_realloc_ret(rbuf, int);
void	rbuf_defragmentation(rbuf);
void	rbuf_debug(rbuf);
void	rbuf_remove_multiline(rbuf rbuf);

#endif /* !LIBRBUF_CORE_H */
