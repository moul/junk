/*
** sapin.c for sapin
**
** Made by manfred touron
** Login   <touron_m@epitech.net>
**
** Started on  Sun Oct 12, 18:53:25 2008 manfred touron
** Last update Sun Oct 12, 18:53:25 2008 manfred touron
*/

#include <stdlib.h>
#include <unistd.h>

#define C(B, E, S)  (1 + (E) * 2 + (B) * 4 + (((B) / 2) * 2) * (((B) + 1) / 2))

int	my_putchar(char c)
{
  return (write(1, &c, 1));
}

int	my_putline(int a, int b, int bmax, int size, char c)
{
  return (a < (C(size - 1, size + 3, size) - bmax - 1) / 2 ?
	  (my_putchar(' ') + my_putline(++a, b, bmax, size, c)) :
	  (b < bmax ? my_putchar(c) + my_putline(a, ++b, bmax, size, c) :
	   my_putchar('\n')));
}

int	sapin_rec(int b, int e, int s)
{
  return (b < s ? (e < b + 4 ? my_putline(0, 0, C(b, e, s), s, '*') +
		   sapin_rec(b, ++e, s) : sapin_rec(++b, 0, s)) :
	  e < s ? my_putline(0, 0, s | 1, s, '|') + sapin_rec(b, ++e, s) : 0);
}

int	sapin(int s)
{
  return (sapin_rec(0, 0, s));
}

int	main(int ac, char **av)
{
  if (ac > 1 && atoi(av[1]) >= 0)
    sapin(atoi(av[1]));
  return (EXIT_SUCCESS);
}
