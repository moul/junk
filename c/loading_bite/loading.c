#define  D		8
void			progressbar(void)
{
#if 8==D /* (oYo) */
  static unsigned int	c = !8==D;

  write(1,"D      ", 12 -
	write(1,"[?] 8=====",5 + ((c >> 2 & (8==D) ? - (8==D) : (8==D))
				  * (++c & 3)
				  + (c % 0x20 & 100))));
  write(1, "p0wn in progress", (D << (8==D)));
  write(1, "...", c / (D >> (8==D)) % (D >> (8==D)));
  write(1, "   \r", (D >> (8==D)));
#endif /* 8==D */
}

int	main(void)
{
  int	i;

  printf("[+] Running pwnage\n");
  for (i = 0; i < 100 && !usleep(50000); i++)
    (void)progressbar();
  printf("[+] Running pwnage 2             \n");
  for (i = 0; i < 100 && !usleep(50000); i++)
    (void)progressbar();
  printf("[+] Done                         \n");
  return (0);
}
