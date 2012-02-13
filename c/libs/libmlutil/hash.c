/**
 * libmlutil/hash.c
 *
 * Copyright (c) Manfred Touron 2008
 */

#ifndef _LIBMU_NOHASH

#include <sys/types.h>
#include <sha.h>
#include <md5.h>
#include <string.h>

#include "debug.h"
#include "common.h"
#include "hash.h"

char		*hash_md5(char *name)
{
  DEBUG_ASCII_IN;
  RETURN (name);
}

char		*hash_sha1(char *name)
{
  SHA_CTX	s;
  char		*hash;

  DEBUG_ASCII_IN;
  SHA1_Init(&s);
  SHA1_Update(&s, (unsigned char *)name, strlen(name));
  hash = SHA1_End(&s, NULL);
  RETURN (hash);
}

#endif
