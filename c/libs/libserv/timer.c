/**
 * mgs/timer.c
 * 
 * Copyright (c) Manfred Touron 2008
 */

#include <sys/time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "server.h"

double			mgs_time_get(void)
{
  struct timeval	tp;
  struct timezone	tzp;

  if (gettimeofday(&tp, &tzp) < 0)
    {
      perror("gettimeofday");
      exit(1);
    }
  return (tp.tv_sec + ((double)tp.tv_usec / 1000000));
}
