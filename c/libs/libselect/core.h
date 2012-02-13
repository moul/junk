/**
 * libcfgfile/libcfgfile.h
 *
 * Copyright (c) Manfred Touron 2008
 */

#ifndef LIBCFGFILE_CORE_H
# define LIBCFGFILE_CORE_H

# include <stddef.h>

# include <librbuf/librbuf.h>

# include "libcfgfile.h"

# define ALLOC(X)		malloc(sizeof(X))
# define ALLOC_N(X, N)		malloc(sizeof(X) * N)

# define BUF_SIZE		1024

typedef struct
{
  const char			*filename;
  int				fd;
  rbuf				rbuf;
}				*cfgfile;

void	cfgfile_init(void);
cfgfile	cfgfile_new(const char *);
cfgfile	cfgfile_find(const char *);
int	cfgfile_cmpfn(void *, void *);
int	_cfgfile_cat_exists(cfgfile, char *);
int	_cfgfile_key_exists(cfgfile, char *, const char *);
char	*_cfgfile_getopt(cfgfile, char *, const char *);

#endif /* !LIBCFGFILE_CORE_H */
