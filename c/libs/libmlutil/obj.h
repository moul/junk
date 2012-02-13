/**
 * libmlutil/obj.h
 *
 * Copyright (c) Manfred Touron 2008
 */

#ifndef LIBMLUTIL_OBJ_H
# define LIBMLUTIL_OBJ_H

# include <libmlutil/types.h>

# define CLASSDESCR(TYPE)	TYPE##_classdescr

# define OBJ_IS(OBJ, TYPE)	obj_is((obj *)OBJ, &CLASSDESCR(TYPE))
# define OBJ_CASE(OBJ, TYPE)	(TYPE *)obj_cast((obj *)OBJ, &CLASSDESCR(TYPE))

# define DECLSTRUCT(STRU)	struct STRU##_struct
# define INTRSTRUCT(STRU)	DECLSTRUCT(STRU);			\
				typedef DECLSTRUCT(STRU) STRU

# define DECLCLASS(OBJ)		DECLSTRUCT(OBJ)
# define INTRCLASS(OBJ)		INTRSTRUCT(OBJ);			\
				extern class_descr CLASSDESCR(OBJ)

# define WATCH_OK(WATCH)	((WATCH)->obj != NULL)

INTRSTRUCT(class_descr);
INTRCLASS(obj);
INTRSTRUCT(watch);

extern bool		obj_is(const obj *, const class_descr *);
extern bool		obj_is_str(const obj *, const char *);
extern const void	*obj_cast(const obj *, const class_descr *);
extern void		destroy_obj(obj *);

DECLCLASS(obj)
{
  class_descr	*obj_type;
  watch		*obj_watches;
  int		flags;
};

# define OBJ_DEST		0x0001

# define OBJ_IS_BEING_DESTROYED(OBJ)	(((obj *)(OBJ))->flags & OBJ_DEST)

# define DYNFUN

typedef void			watch_handler(watch *, obj *);

# define WATCH_INIT		{NULL, NULL, NULL, NULL}

DECLSTRUCT(watch)
{
  obj				*obj;
  watch				*next;
  watch				*prev;
  watch_handler			*handler;
};

extern bool	watch_setup(watch *, obj *, watch_handler *);
extern void	watch_reset(watch *);
extern bool	watch_ok(watch *);
extern void	watch_init(watch *);
extern void	watch_call(obj *);


#endif /* !LIBMLUTIL_OBJ_H */
