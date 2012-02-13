/**
 * libservices/tester.c
 *
 * Copyright (c) Manfred Touron 2008
 */

#include <stdarg.h>
#include <stdio.h>

#include "module.h"
#include "client.h"

SERVICE_CALLBACK(test_service)
{
  printf("test_service called (%d)\n", ARGC);
  CALLV(printf, 0);
  return ("OK");
}

SERVICE_CALLBACK(test2_service)
{
  printf("test2_service called\n");
  printf("arg: [%s]\n", (char *)ARGV(0));
  return ("OK");
}

int	main(int ac, char **av)
{
  char	*ret;

  printf("[+] init\n");

  printf("[+] Add service test\n");
  service_add("test", test_service,
	      "super service de test qui sert a rien");
  printf("[+] Add service test\n");
  service_add("test2", test2_service,
	      "super service de test2 qui sert toujours a rien");

  printf("[+] List services\n");
  services_list();

  printf("[+] Call service test\n");
  ret = SERVICE_CALL("test", "bite [%s]\n", "bla");

  printf("[+] test return [%s]\n", ret);

  printf("[+] uninit\n");
  return (0);
  (void)ac;
  (void)av;
}
