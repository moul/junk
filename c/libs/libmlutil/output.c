/**
 * libmlutil/output.c
 *
 * Copyright (c) Manfred Touron 2008
 */

#include <stdio.h>
#include <string.h>
#include <errno.h>

#include "output.h"
#include "util.h"
#include "locale.h"
#include "misc.h"

static void		default_warn_handler(const char *);

static bool		verbose_mode = FALSE;
static int		verbose_indent_lvl = 0;
static bool		progname_enable = TRUE;
static warn_handler	*current_warn_handler = default_warn_handler;

# define INDENTATOR_LENGTH	4

static char		indentator[] = {' ', ' ', ' ', ' '};

static void	do_dispatch_message(const char *);

void		verbose(const char *p, ...)
{
  va_list	args;

  va_start(args, p);
  verbose_v(p, args);
  va_end(args);
  return ;
}

void	verbose_v(const char *p, va_list args)
{
  int	i;

  if (verbose_mode)
    {
      for (i = 0; i < verbose_indent_lvl; i++)
	writef(stdout, indentator, INDENTATOR_LENGTH);
      vprintf(p, args);
      fflush(stdout);
    }
  return ;
}

void	verbose_enable(bool enable)
{
  verbose_mode = enable;
  return ;
}

void	warn_progname_enable(bool enable)
{
  progname_enable = enable;
  return ;
}

static void	put_prog_name()
{
  const char	*progname;

  if (!progname_enable)
    return ;
  progname = libmlutil_progname();
  if (progname == NULL)
    return ;
  fprintf(stderr, "%s: ", (char *)progname);
  return ;
}

static void	fallback_warn()
{
  put_prog_name();
  fprintf(stderr, TR("Oops. Compilation failed: %s"), strerror(errno));
  return ;
}

#define CALL_V(NAME, ARGS)						\
  if (1)								\
    {									\
      va_list args;							\
      va_start(args, p);						\
      NAME ARGS;							\
      va_end(args);							\
    }									\

#define DO_DISPATCH(NAME, ARGS)						\
  if (1)								\
    {									\
      char	*msg;							\
									\
      if ((msg = NAME ARGS) != NULL)					\
	{								\
	  do_dispatch_message(msg);					\
	  free(msg);							\
	}								\
      else								\
	fallback_warn();						\
    }

void	mlutil_asprintf(char **ret, const char *p, ...)
{
  *ret = NULL;
  CALL_V(vasprintf, (ret, p, args));
  if (*ret == NULL)
    warn_err();
  return ;
}

void	mlutil_vasprintf(char **ret, const char *p, va_list args)
{
  *ret = NULL;
  vasprintf(ret, p, args);
  if (*ret == NULL)
    warn_err();
  return ;
}

void	warn(const char *p, ...)
{
  CALL_V(warn_v, (p, args));
  return ;
}

void	warn_obj(const char *obj, const char *p, ...)
{
  CALL_V(warn_obj_v, (obj, p, args));
  return ;
}

void	warn_obj_line(const char *obj, int line, const char *p, ...)
{
  CALL_V(warn_obj_line_v, (obj, line, p, args));
  return ;
}

void	warn_v(const char *p, va_list args)
{
  DO_DISPATCH(errmsg_v, (p, args));
  return ;
}

void	warn_obj_v(const char *obj, const char *p, va_list args)
{
  warn_obj_line_v(obj, -1, p, args);
  return ;
}

void	warn_obj_line_v(const char *obj, int line, const char *p, va_list args)
{
  DO_DISPATCH(errmsg_obj_line_v, (obj, line, p, args));
  return ;
}

void	warn_err(void)
{
  DO_DISPATCH(errmsg_err, ());
  return ;
}

void	warn_err_obj(const char *obj)
{
  DO_DISPATCH(errmsg_err_obj, (obj));
  return ;
}

void	warn_err_obj_line(const char *obj, int line)
{
  DO_DISPATCH(errmsg_err_obj_line, (obj, line));
  return ;
}

#define CALL_V_RET(NAME, ARGS)						\
  char		*ret;							\
  va_list	args;							\
									\
  va_start(args, p);							\
  ret = NAME ARGS;							\
  va_end(args);								\
  return (ret);

char	*errmsg(const char *p, ...)
{
  CALL_V_RET(errmsg_v, (p, args));
}

char	*errmsg_obj(const char *obj, const char *p, ...)
{
  CALL_V_RET(errmsg_obj_v, (obj, p, args));
}

char	*errmsg_obj_line(const char *obj, int line, const char *p, ...)
{
  CALL_V_RET(errmsg_obj_line_v, (obj, line, p, args));
}

char	*errmsg_obj_v(const char *obj, const char *p, va_list args)
{
  return (errmsg_obj_line_v(obj, -1, p, args));
}

char	*errmsg_v(const char *p, va_list args)
{
  char	*res;

  mlutil_vasprintf(&res, p, args);
  return (res);
}

char	*errmsg_obj_line_v(const char *obj, int line, const char *p,
			   va_list args)
{
  char	*res1;
  char	*res2;
  char	*res3;

  res1 = NULL;
  if (obj != NULL)
    {
      if (line > 0)
	mlutil_asprintf(&res1, "%s:%d: ", obj, line);
      else
	mlutil_asprintf(&res1, "%s: ", obj);
    }
  else
    {
      if (line > 0)
	mlutil_asprintf(&res1, "%d: ", line);
    }
  mlutil_vasprintf(&res2, p, args);
  if (res1 != NULL)
    {
      if (res2 == NULL)
	{
	  free(res1);
	  return (NULL);
	}
      res3 = scat(res1, res2);
      free(res1);
      free(res2);
      return (res3);
    }
  return (res2);
}

char	*errmsg_err(void)
{
  char	*res;

  mlutil_asprintf(&res, "%s\n", strerror(errno));
  return (res);
}

char	*errmsg_err_obj(const char *obj)
{
  char	*res;

  if (obj != NULL)
    {
      mlutil_asprintf(&res, "%s: %s\n", obj, strerror(errno));
      return (res);
    }
  return (errmsg_err());
}

char	*errmsg_err_obj_line(const char *obj, int line)
{
  char	*res;

  if (line > 0)
    {
      if (obj != NULL)
	mlutil_asprintf(&res, "%s:%d: %s\n", obj, line, strerror(errno));
      else
	mlutil_asprintf(&res, "%d: %s\n", line, strerror(errno));
    }
  return (errmsg_err_obj(obj));
}

void	die(const char *p, ...)
{
  CALL_V(die_v, (p, args));
}

void	die_v(const char *p, va_list args)
{
  set_warn_handler(NULL);
  warn_v(p, args);
  exit(EXIT_FAILURE);
}

void	die_obj(const char *obj, const char *p, ...)
{
  CALL_V(die_obj_v, (obj, p, args));
}

void	die_obj_v(const char *obj, const char *p, va_list args)
{
  set_warn_handler(NULL);
  warn_obj_v(obj, p, args);
  exit(EXIT_FAILURE);
}

void	die_obj_line(const char *obj, int line, const char *p, ...)
{
  CALL_V(die_obj_line_v, (obj, line, p, args));
}

void	die_obj_line_v(const char *obj, int line, const char *p, va_list args)
{
  set_warn_handler(NULL);
  warn_obj_line_v(obj, line, p, args);
  exit(EXIT_FAILURE);
}

void	die_err(void)
{
  set_warn_handler(NULL);
  warn_err();
  exit(EXIT_FAILURE);
}

void	die_err_obj(const char *obj)
{
  set_warn_handler(NULL);
  warn_err_obj(obj);
  exit(EXIT_FAILURE);
}

void	die_err_obj_line(const char *obj, int line)
{
  set_warn_handler(NULL);
  warn_err_obj_line(obj, line);
  exit(EXIT_FAILURE);
}

static void	default_warn_handler(const char *message)
{
  put_prog_name();
  fprintf(stderr, "%s", message);
  putc('\n', stderr);
}

static void	do_dispatch_message(const char *message)
{
  if (current_warn_handler != NULL)
    current_warn_handler(message);
  else
    default_warn_handler(message);
}

warn_handler	*set_warn_handler(warn_handler *handler)
{
  warn_handler	*old;

  old = current_warn_handler;
  current_warn_handler = (handler != NULL ? handler : default_warn_handler);
  return (old);
}
