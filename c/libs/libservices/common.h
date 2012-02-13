/**
 * libservices/common.h
 *
 * Copyright (c) Manfred Touron 2008
 */

#ifndef LIBSERVICES_COMMON_H
# define LIBSERVICES_COMMON_H

# include <liblc/lc.h>

# define SERVICE_CALLBACK(NAME)	char	*NAME(CLLBCK_ARGS argv)

typedef struct
{
  int			intret;
  void			*ptrret;
  int			type;
  size_t		ptrsize;
}			svcret;

typedef char *		svcfn(CLLBCK_ARGS);

typedef struct
{
  const char		*name;
  char			*(*fn)(CLLBCK_ARGS);
  const char		*descr;
}			*svc;

enum
  {
    TYPE_INT,
    TYPE_PTR
  };

# define RETURN_INT(X)	return ((svcret){X, NULL, TYPE_INT, sizeof(X)})
# define RETURN_PTR(X)	return ((svcret){0, X, TYPE_PTR, sizeof(X)})
# define GET_INT(X)	(int)(X.type == TYPE_INT ? X.intret : 0)
# define GET_PTR(X)	(viod *)(X.type == TYPE_PTR ? )

#endif /* !LIBSERVICES_COMMON_H */
