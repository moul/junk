/**
 * libcfgfile/libcfgfile.h
 *
 * Copyright (c) Manfred Touron 2008
 */

#ifndef LIBCFGFILE_H
# define LIBCFGFILE_H

char	*cfgfile_getopt(const char *, char *, const char *);
int	cfgfile_cat_exists(const char *, char *);
int	cfgfile_key_exists(const char *, char *, const char *);

#endif /* !LIBCFGFILE_H */
