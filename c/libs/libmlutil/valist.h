/**
 * libmlutil/valist.h
 *
 * Copyright (c) Manfred Touron 2008
 */

#ifndef LIBMLUTIL_VALIST_H
# define LIBMLUTIL_VALIST_H

# include <string.h>

# define VASIZE(TYPE)		(((sizeof(TYPE) + sizeof(int) - 1) /	\
				  sizeof(int)) * sizeof(int))

# define CALLBACK_V(NAME)	int	NAME(int argc, va_list varg)
# define CALLBACK(NAME)		int	NAME(VARGS_T argv)

# define ARG(POS, TYPE)		(*(TYPE *)((varg) + (POS) * VASIZE(TYPE)))
# define ARGP(POS)		(*(va_list*)((varg) + (POS) * VASIZE(int)))

# define VARGS_T		void **

# if 0
# define EVENT_CALL(NAME, ...)	event_call(NAME, (void *[]){__VA_ARGS__})
# define ARGC			(sizeof(argv) / sizeof(*argv))
# else
# define EOARG			-42424342
static __inline int		event_argc(VARGS_T argv)
{
  int	argc;

  for (argc = 0; (int)argv[argc] != EOARG; argc++)
    ;
  return (argc);
}
# define VARGS(...)		(void *[]){__VA_ARGS__, (void *)EOARG}
# define EVENT_CALL(NAME, ...)	event_call(NAME, VARGS(__VA_ARGS__))
# define ARGC			event_argc((void *)argv)
# endif

# define ARGV(POS)		argv[POS]
# define ARGS			argv
# define CARGV(POS)		(void *)ARGV(POS)

# define CALLV(FN, POS)	{						\
    switch (ARGC) { case 0:						\
	break; case 1: FN(CARGV(POS), (void *)EOARG);			\
	break; case 2: FN(CARGV(POS), CARGV(POS + 1));			\
	break; case 3: FN(CARGV(POS), CARGV(POS + 1),			\
			  CARGV(POS + 2));				\
	break; case 4: FN(CARGV(POS), CARGV(POS + 1),			\
			  CARGV(POS + 2), CARGV(POS + 3));		\
	break; case 5: FN(CARGV(POS), CARGV(POS + 1),			\
			  CARGV(POS + 2), CARGV(POS + 3),		\
			  CARGV(POS + 4));				\
	break; case 6: FN(CARGV(POS), CARGV(POS + 1),			\
			  CARGV(POS + 2), CARGV(POS + 3),		\
			  CARGV(POS + 4), CARGV(POS + 5));		\
	break; }}


# define CALLVB(FN, POS, ...)	{					\
    switch (ARGC) { case 0:						\
	break; case 1: FN(__VA_ARGS__, CARGV(POS));			\
	break; case 2: FN(__VA_ARGS__, CARGV(POS), CARGV(POS + 1));	\
	break; case 3: FN(__VA_ARGS__, CARGV(POS), CARGV(POS + 1),	\
			  CARGV(POS + 2));				\
	break; case 4: FN(__VA_ARGS__, CARGV(POS), CARGV(POS + 1),	\
			  CARGV(POS + 2), CARGV(POS + 3));		\
	break; case 5: FN(__VA_ARGS__, CARGV(POS), CARGV(POS + 1),	\
			  CARGV(POS + 2), CARGV(POS + 3),		\
			  CARGV(POS + 4));				\
	break; case 6: FN(__VA_ARGS__, CARGV(POS), CARGV(POS + 1),	\
			  CARGV(POS + 2), CARGV(POS + 3),		\
			  CARGV(POS + 4), CARGV(POS + 5));		\
	break; }}

# define CALLVB2(FN, POS, ...)	{					\
    switch (strlen(#__VA_ARGS__)) { case 0:				\
	switch (ARGC) { case 0:						\
	    break; case 1: FN(CARGV(POS));				\
	    break; case 2: FN(CARGV(POS), CARGV(POS + 1));		\
	    break; }							\
	break; default:							\
	break; }};

#endif /* !LIBMLUTIL_VALIST_H */
