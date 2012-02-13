/**
 * mgs/tester.c
 * 
 * Copyright (c) Manfred Touron 2008
 */

#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "server.h"

int		main(int argc, char **argv)
{
  t_mgs_context	context;

  api_init(&context);
  mgs_api_callback(MGS_CALLBACK_USAGE, &argc, argv);
  if (argc < 2)
    usage(argv[0]);
  mgs_get_context_ptr(&context);
  context.fd = -1;
  context.clients = NULL;
  VERBOSE(printf("[+] Initialisation\n"));
  if ((context.fd = create_tcp_server(atoi(argv[argc - 1]))) < 0)
    {
      VERBOSE(printf( "[-] Problem while creating new TCP server.\n"));
      exit(1);
    }
  VERBOSE(printf("[+] Server is listening on port %d\n", atoi(argv[1])));
  routine(&context);
  return (0);
}

t_mgs_context		*mgs_get_context_ptr(t_mgs_context *ctx)
{
  static t_mgs_context	*ptr = (t_mgs_context *)-1;

  if (ptr == (t_mgs_context *)-1)
    ptr = ctx;
  return (ptr);
}

void	usage(char *progname)
{
  printf("usage : %s PORT\n", progname);
  exit (0);
}
