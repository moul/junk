/**
 * libgetopt/libgetopt.h
 *
 * Copyright (c) Manfred Touron 2008
 */

#ifndef LIBGETOPT_H
# define LIBGETOPT_H

int	getopt_init(int, char **);
int	getopt_check(const char *);
int	getopt_exists(const char);
int	getopt_exists_all(const char *);
char	*getopt_get(const char, const char *);
void	usage(const char *);

#endif /* !LIBGETOPT_H */
