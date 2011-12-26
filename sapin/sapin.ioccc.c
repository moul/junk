#define C(B, E, S)  (1 + (E) * 2 + (B) * 4 + (((B) / 2) * 2) * (((B) + 1) / 2))

int	__(int a, int b, int d, int s, char c)
{
  return (a < (C(s - 1, s + 3, s) - d - 1) / 2 ?
	  (write(1, " ", 1) + __(++a, b, d, s, c)) :
	  (b < d ? write(1, &c, 1) + __(a, ++b, d, s, c) :
	   write(1, "\n", 1)));
}

int	_(int br, int e, int a, int b, int s)
{
  return (br < s ? (e < br + 4 ? __(0, 0, C(br, e, s), s, '*') +
		    _(br, ++e, 0, 0, s) : _(++br, 0, 0, 0, s)) :
	  e < s ? __(0, 0, s | 1, s, '|') + _(br, ++e, 0, 0, s) : 0);
}

int	main(int c, char **v)
{
  return (c > 1 && atoi(1[v]) >= 0 ? _(0, 0, 0, 0, atoi(1[v])) : 0);
}
