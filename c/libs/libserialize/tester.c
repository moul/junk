/**
 * libserialize/tester.c
 *
 * Copyright (c) Manfred Touron 2008
 */

#include <stdio.h>

#include "libserialize.h"

STRUCT(s_test,
  {
    char	*name;
    int		bite;
    char	*foo;
  })
TYPEDEF(s_test, test);

int		main(int ac, char **av)
{
  test		t;
  char		*serialized;

  t.name = "bla";
  t.bite = 42;
  t.foo = "sandouiche";
  printf("[+] Initialisation\n");

  printf("[+] Add s_test\n");
  SERIALIZE_ADD(s_test, test);

  printf("[+] Dump s_test\n");
  serialize_dump("s_test");

  printf("[+] Serialize s_test\n");
  serialized = SERIALIZE(&t, s_test);
  printf("[+] Serialized\n");
  printf("[+] Result: [%s]\n", serialized);

  printf("[+] Uninitialisation\n");
  return (0);
  (void)ac;
  (void)av;
}
