/**
 * libcfgfile/tester.c
 *
 * Copyright (c) Manfred Touron 2008
 */

#include <stdio.h>

#include "libcfgfile.h"

void	test(const char *filename, char *category, const char *key)
{
  char	*res;

  printf("   [+] Preliminary tests\n");
  if (!cfgfile_cat_exists(filename, category))
    printf("   [-] category %s does not exists\n", category);
  else
    {
      printf("   [+] category %s exists\n", category);
      if (!cfgfile_key_exists(filename, category, key))
	printf("   [-] key %s does not exists\n", key);
      else
	{
	  printf("   [+] key %s exists\n", key);
	  res = cfgfile_getopt(filename, category, key);
	  printf("   [+] result: [%s]\n", res);
	}
    }
  return ;
}

#define TEST(FILE, CAT, KEY)						\
  printf("[+] Test: file=%s, cat=%s, key=%s\n", FILE, CAT, KEY);	\
  test(FILE, CAT, KEY);

int	main(int ac, char **av)
{
  char	*filename;

  filename = "example.conf";
  printf("[+] Initialisation\n");
  TEST(filename, "toto", "tata");
  printf("[+] Uninitialisation\n");
  return (0);
  (void)ac;
  (void)av;
}
