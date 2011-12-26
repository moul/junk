#include <stdio.h>

//#define m(o,O) !!n(o,O)
//n(char*_,char*$){return!*_&&!*$?1:*_==*$?n(_+1,$+1):*$==42?(*_?n(_+1,$):0)+n(_,++$):0;}

int	nmatch(char *a, char *b)
{
  return !*a && !*b ? 1 : *b == '*' ? (*a ? nmatch(a + 1, b) : 0) + nmatch(a, b + 1) : *a == *b ? nmatch(a + 1, b + 1) : 0;
}

w(char*_,char*$){return!*_&&!*$?1:*_==*$?n(_+1,$+1):*$==42?(*_?n(_+1,$):0)+n(_,++$):0;}//8=D

#define b(o,O)\
!!n(o,O)// 8==D
z(char*_,char*$
){return!*_&&!*
$?1:*$==42?(*_?
n(_+1,$):0)+n(_
,++$):*_==*$?n(
_+1,$+1):0;}//-

n(char*_,char*$)<%{<%{
return!*_&&!*$?!0:*$==
42?(*_?n(_+1,$):0)+n(_
#define m(o,O)!!n(o,O)
,++$):*_==*$?n(_+1,$+1
):0;}%>}<%/*8==D*/%>%>

/* int	main() */
/* { */
/*   printf("%d\n", n("hello", "***")); */
/*   printf("%d\n", m("hello", "***")); */
/* } */
