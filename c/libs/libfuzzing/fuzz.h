/**
 * libfuzzing/fuzz.h
 *
 * Copyright (c) Manfred Touron 2008
 */

#ifndef LIBFUZZING_FUZZ_H
# define LIBFUZZING_FUZZ_H

extern bool	libfuzzing_init(void);
extern void	libfuzzing_uninit(void);

extern int	fuzz_connect(char *, int);
extern void	fuzz_send(int, char *);

#endif /* LIBFUZZING_FUZZ_H */
