#include "xmalloc.h"

int	main(int ac, char **av)
{
  void	*ptr;

  ptr = malloc(42);
  ((char *)ptr)[0] = 0;
  ((char *)ptr)[41] = 0;
  ptr = realloc(ptr, 43);
  ((char *)ptr)[0] = 0;
  ((char *)ptr)[42] = 0;
  ptr = malloc(44);
  ptr = malloc(45);
  free(ptr);
  free(ptr);
  show_xmalloc();
  return (0);
  (void)ac;
  (void)av;
}
