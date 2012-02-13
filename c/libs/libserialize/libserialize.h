/**
 * libserialize/libserialize.h
 *
 * Copyright (c) Manfred Touron 2008
 */

#ifndef LIBSERIALIZE_H
# define LIBSERIALIZE_H

# define STRUCT(NAME, CONTENT)					\
  struct NAME CONTENT;						\
  char *_struct_ ## NAME ## _name = #NAME;			\
  char *_struct_ ## NAME ## _content = #CONTENT;		\
  char *_struct_ ## NAME ## _alias = NULL;

# define TYPEDEF(STRUCT, ALIAS)			\
  typedef struct STRUCT	ALIAS;
#if 0
  _struct_ ## STRUCT ## _alias = #ALIAS;
#endif

# define SERIALIZE_ADD(N, A)	serialize_add(_struct_ ## N ## _name,	\
					      _struct_ ## N ## _content, \
					      #A);

# define SERIALIZE(PTR, TYPE)	serialize((void *)PTR, #TYPE)

typedef struct		s_serialize
{
  char			*name;
  char			*content;
  char			*alias;
}			srlz;

void	serialize_add(char *, char *, char *);
int	serialize_dump(const char *);
srlz	*serialize_get(const char *);
char	*serialize(void *, const char *);

#endif /* !LIBSERIALIZE_H */
