/**
 * libfuzzing/fuzzing.c
 *
 * Copyright (c) Manfred Touron 2008
 */

#include <libnet/client.h>

#include <libmlutil/types.h>

bool	libfuzzing_init(void)
{
  return (TRUE);
}

void	libfuzzing_uninit(void)
{
  return;
}

int	fuzz_connect(char *hostname, int port)
{
  return (libnet_connect((const char *)hostname, port));
}

void	fuzz_send(int fd, const char *str)
{
  
}
