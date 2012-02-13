/**
 * libgetopt/tester.c
 *
 * Copyright (c) Manfred Touron 2008
 */

#include <stdio.h>

#include "libgetopt.h"

void	test(const char *fmt, int ac, char **av)
{
#if 0
  printf("   [+] debut du test\n");
  printf("   [+] getopt_init\n");
#endif
  if (!getopt_init(ac, av))
    {
      printf ("getopt_init: bad args\n");
      return ;
    }
  if (!getopt_exists_all(fmt))
    printf("getopt_exists_all: nop\n");
#if 0
  printf("   [+] fin du test\n");
#endif
  return ;
}

#define TEST(FMT, AC, ...)					\
  printf("[+] Test avec "#FMT", "#AC", "#__VA_ARGS__"\n");	\
  test(FMT, AC, (char *[]){av[0], __VA_ARGS__, NULL});

int	main(int ac, char **av)
{
  printf("[+] Test avec a:o:f, ac, av + 1\n");
  test("a:o:f", ac, av);

  TEST("ao:", 3, "-a", "-o");
  TEST("ao:", 4, "-a", "-o");
  TEST("af:", 3, "-a", "-o");
  printf("[+] fin de tous les tests\n");

  usage("[j'aime] [les] [bites]");

  return (0);
  (void)ac;
  (void)av;
}
