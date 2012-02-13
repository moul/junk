/**
 * mgs/server.h
 *
 * Copyright (c) Manfred Touron 2008
 */

#ifndef _MGS_SERVER_H
# define _MGS_SERVER_H

/**********************/
/* INCLUDES           */
/**********************/

# include <sys/select.h>
# include <sys/types.h>
# include <sys/socket.h>
# include <netinet/in.h>
# include <arpa/inet.h>
# include <netdb.h>

# include "xmalloc.h"
# include "api.h"
# include "timer.h"

/**********************/
/* DEFINES            */
/**********************/


# define COLOR(id)		((id) % 6 + 31)

# define GETIP(A,I)		(((A)>>(I*8))&0xFF)

# define BUF_SIZE		8092

# define SET_ONLY_READ		2
# define SET_ONLY_WRITE		4
# define SET_READ_WRITE		6

# define STR(X)			#X
# define XSTR(X)		STR(X)

# define xmalloc malloc
/**********************/
/* STRUCTURES         */
/**********************/

/**********************/
/* PROTOTYPES         */
/**********************/
/* main.c */
void		usage(char *);

/* misc.c */
int		xbind(int, struct sockaddr *);
int		xlisten(int);
int		xsocket(struct protoent *);
int		xioctl(t_mgs_client *, t_mgs_client *, int *);
/*void		*xmalloc(unsigned int);*/

/* net.c */
void		tunneling_line(t_mgs_client *, char *, int);
void		accept_mgs_new_client(t_mgs_context *);
void		write_to_client(t_mgs_client *);
int		create_tcp_server(int);

/* buffer.c */
int		read_from_client(t_mgs_client *);
char		*get_buffin_next_line(t_mgs_client *);
char		*get_splitted_buffin_next_line(t_mgs_client *);
int		check_read_from_client(t_mgs_client *, int *);

/* select.c */
void		check_fdset(fd_set *, fd_set *, t_mgs_context *);
int		set_my_fd(t_mgs_client *, fd_set *, fd_set *, int );
int		init_mgs_fdset(fd_set *, fd_set *, t_mgs_context *);

/* parser.c */
int		cmd_null(t_mgs_client *, char *);
int		cmd_debug(t_mgs_client *, char *);
int		parser(t_mgs_client *, char *);

/* routine.c */
void		routine(t_mgs_context *);
void		net_mgs_traitement(t_mgs_context *);

/* client.c */
t_mgs_client	*client_init_mgs_new(int);
t_mgs_client	*client_add(t_mgs_context *, int);
void		client_uninit(t_mgs_client *);

/* api.c */
void		api_init(t_mgs_context *);

/* VERBOSE */
# ifndef NVERBOSE
#  define VERBOSE(Msg)			{ Msg; }
# else
#  define VERBOSE(Msg)			
# endif /* !NVERBOSE */

#endif /* !_MGS_SERVER_H */
