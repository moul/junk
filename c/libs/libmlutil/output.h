/**
 * libmlutil/output.h
 *
 * Copyright (c) Manfred Touron 2008
 */

#ifndef LIBMLUTIL_OUTPUT_H
# define LIBMLUTIL_OUTPUT_H

# include <stdarg.h>
# include "types.h"

# if __STDC_VERSION__ >= 199901L
#  define WARN_FUNC(...)	warn_obj(__func__, __VA_ARGS__)
#  define WARN_ERR_FUNC()	warn_err_obj(__func__)
# else /* __STDC_VERSION__ >= 199901L */
#  define WARN_FUNC		warn
#  define WARN_ERR_FUNC()	warn_err()
# endif /* !__STDC_VERSION__ >= 199901L */

typedef void		warn_handler(const char *);

extern warn_handler	*set_warn_handler(warn_handler *);

extern void	verbose(const char *, ...);
extern void	verbose_v(const char *, va_list);
extern void	verbose_enable(bool);
extern int	verbose_indent(int);

extern void	warn_progname_enable(bool);

extern void	die(const char *, ...);
extern void	die_v(const char *, va_list);

extern void	die_obj(const char *, const char *, ...);
extern void	die_obj_v(const char *, const char *, va_list);
extern void	die_obj_line(const char *, int, const char *, ...);
extern void	die_obj_line_v(const char *, int, const char *, va_list);

extern void	die_err();
extern void	die_err_obj(const char *);
extern void	die_err_obj_line(const char *, int);

extern void	warn(const char *, ...);
extern void	warn_v(const char *, va_list);

extern void	warn_obj(const char *, const char *, ...);
extern void	warn_obj_v(const char *, const char *, va_list);
extern void	warn_obj_line(const char *, int, const char *, ...);
extern void	warn_obj_line_v(const char *, int, const char *, va_list);

extern void	warn_err();
extern void	warn_err_obj(const char *);
extern void	warn_err_obj_line(const char *, int);

extern char	*errmsg(const char *, ...);
extern char	*errmsg_v(const char *, va_list);

extern char	*errmsg_obj(const char *, const char *, ...);
extern char	*errmsg_obj_v(const char *, const char *, va_list);
extern char	*errmsg_obj_line(const char *, int, const char *, ...);
extern char	*errmsg_obj_line_v(const char *, int, const char *, va_list);

extern char	*errmsg_err();
extern char	*errmsg_err_obj(const char *);
extern char	*errmsg_err_obj_line(const char *, int);

extern void	mlutil_asprintf(char **, const char *, ...);
extern void	mlutil_vasprintf(char **, const char *, va_list);

#endif /* !LIBMLUTIL_OUTPUT_H */
