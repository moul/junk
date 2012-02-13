/**
 * libevent/tester.c
 *
 * Copyright (c) Manfred Touron 2008
 */

#include <stdarg.h>
#include <stdio.h>

#include "libevent.h"

#define TESTER_NEW_CALLBACK(NAME)				\
  CALLBACK(NAME)						\
  {								\
    printf("[" #NAME "] called (%d)\n", ARGC);			\
    CALLV(printf, 0);						\
    return (1);							\
  }								\
  int	NAME(void *[])

TESTER_NEW_CALLBACK(aaa);
TESTER_NEW_CALLBACK(bbb);
TESTER_NEW_CALLBACK(ccc);
TESTER_NEW_CALLBACK(ddd);
TESTER_NEW_CALLBACK(eee);

CALLBACK(nounours)
{
  return (1);
  (void)argv;
}

int	main(int ac, char **av)
{
  printf("[+] init\n");
  event_add_handler("toto", aaa);
  event_add_handler("toto2", aaa);
  event_add_handler("toto", bbb);
  event_add_handler("toto3", aaa);
  event_add_handler("toto", ccc);
  event_add_handler("toto", ddd);
  event_add_handler("toto", aaa);
  event_add_handler("toto", bbb);
  event_add_handler("toto", ccc);
  event_add_handler("toto", ccc);
  event_add_handler("toto", ddd);
  event_del_handler("toto", ccc);
  event_add_handler("toto", ddd);
  event_del_handler("toto2", aaa);
  event_add_handler("toto2", aaa);
  event_add_handler("toto2", aaa);
  event_add_handler("voiture", bbb);
  event_add_handler("voiture", aaa);
  events_debug();
  EVENT_CALL("toto2", "tata [%s] [%s]\n", "titi", "tutu");
  EVENT_CALL("toto2", "tata [%s]\n", "titi");
  EVENT_CALL("voiture", "blabla : [%s]\n", "bite");
  printf("[+] uninit\n");
  return (0);
  (void)ac;
  (void)av;
}
