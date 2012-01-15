#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define ABS(n)(n<0?-(n):n)
typedef struct s_stock_par{int size_param;char*str;char*copy;char**tab;}t_stock_par;
typedef struct s_list{void*data;struct s_list*next;}t_list;

#define PC my_putchar
#define PS my_putstr
#define SL my_strlen
#define WR write
#define R return
#define I int
#define V void
#define C char
#define S struct s_stock_par
#define L struct s_list
#define PN my_putnbr
#define PU my_putunbr
#define U unsigned
#define AA my_aff_alpha
#define AR my_aff_revalpha
#define AC my_aff_chiffre
#define IN my_isneg
#define PR my_power_rec
#define X(N)//
#define M X(malloc)
#define W while

I PC(C _){R WR(1,&_,1);}
I SL(C*_){R*_?SL(_+1)+1:0;}
I PS(C*_){R WR(1,_,SL(_));}
I _m(C _,C o,I O){R PC(_)+(_!=o?_m(_+O,o,O):0);}
I AA(){R _m('a','z',1);}
I AR(){R _m('z','a',-1);}
I AC(){R _m('0','9',1);}
I IN(I _){R PC('P'-2*(_<0));}
I PU(U I _){R (_>10?PU(_/10):0)+PC(_%10+'0');}
I PN(I _){R _<0?PC('-')+PU(-_):PU(_);}
I PR(I o,I O){R O<0?0:(O>0?o:1)*(O>0?PR(o,O-1):1);}
I _b(I _,I o,I O){R o?_b(_*10+O-o,o-1,O):_;}
I _c(I o){R (o%10>o/10%10)*(o>10?_c(o/10):1);}
I _a(I _,I o,I O){R (_c(_)?PS(_!=o?", ":"")+PS(_<O/10?"0":"")+PN(_):0)+(_<O?_a(_+1,o,O):0);}
I my_aff_comb(){R(_a(12,12,999));}
I my_aff_combn(I n){R(_a(_b(0,n,n),_b(0,n,n),PR(10,n)));}
I my_swap(I*a,I*b){I c=*a;*a=*b;*b=c;R 0;}
I _n(C*s,I n){R*s>='0'&&*s<='9'?_n(s+1,n*10+*s-'0'):n;}
I _s(C*_,I o,C**O){R (*_=='-'||*_=='+')?!++*O+_s(_+1,o*(*_=='-'?-1:1),O):o;}
I my_getnbr(C*s){R _s(s,1,&s)*_n(s, 0);}
I my_factorielle_rec(I n){R n<0?0:n?n*my_factorielle_rec(n-1):1;}
I my_factorielle_it(I n){I r=1;if(n<0)R 0;W(n&&(r*=n--));R r;}
I my_power_it(I n,I p){I r=1;W(p--&&(r*=n));R r;}
I my_strcmp(C*a,C*b){R *a!=*b?*a-*b:*a||*b?my_strcmp(a+1,b+1):0;}
I my_strncmp(C*a,C*b,I n){R n<2||*a!=*b?*a-*b:*a||*b?my_strncmp(a+1,b+1,n-1):0;}

I my_evil_str(C*s);
I my_aff_comb2();
I my_sort_int_tab(I*t,I s);
I my_8r1();
I my_8r2();
I my_square_root(I n);
I my_is_prime(I n);
I my_find_prime_sup(I n);
C*my_strcpy(C*d,C*s);
C*my_strncpy(C*d,C*s,I n);
C*my_revstr(C*d);
C*my_strstr(C*d,C*s);
C*my_strupcase(C*s);
C*my_strlowcase(C*s);
C*my_strcapitalize(C*s);
I my_str_isalpha(C*s);
I my_str_isnum(C*s);
I my_str_islower(C*s);
I my_str_isupper(C*s);
I my_str_isprintable(C*s);
I my_putnbr_base(I n,C*b);
I my_getnbr_base(C*n,C*b);
I my_showstr(C*s);
I my_showmem(C*s,I l);
C*my_strcat(C*a,C*b);
C*my_strncat(C*a,C*b,I n);
C*my_strlcat(C*a,C*b,I l);
C*my_strdup(C*s);
C*convert_base(C*n,C*f,C*t);
C*sum_params(I c,C**v);
C**my_str_to_wordtab(C*s);
I my_show_to_wordtab(C**t);
S*my_param_to_tab(I c,C**v);
I my_show_tab(S*p);
I is_big_endian();
I my_sort_tab(V*t,I(*c)());
I my_sort_wordtab(C**t);

L*my_params_in_list(I c,C**v);
I my_list_size(L*b);
I my_rev_list(L**b);
I my_apply_on_list(L*b,I(*f)());
I my_apply_on_eq_in_list(L*b,I(*f)(),V*d,I(*c)());
V*my_find_elm_eq_in_list(L*b,V*d,I(*c)());
L*my_find_node_eq_in_list(L*b,V*d,I(*c)());
I my_rm_all_eq_from_list(L**b,V*d,I(*c)());
I my_add_list_to_list(L**a,L*b);
I my_sort_list(L**b,I(*c)());
I my_put_elem_in_sort_list(L**b,V*d,I(*c)());
I my_add_sort_list_to_sort_list(L**a,L*b,I(*c)());

#define TEST(cmd, esp)						\
   {								\
    int nb;							\
    write(1, "test de ", 8);					\
    write(1, #cmd, strlen(#cmd));				\
    write(1, "\r\t\t\t\t\t<", 7);				\
    nb = (int)(cmd);						\
    printf("> \r\t\t\t\t\t\t\t\t\t\t\t(%d)\t%s (%d)\n", nb,	\
	   (nb == esp ? "  " : ":("), esp);			\
  }

I main_1(I c,C**v)
{
  I i;

  TEST(my_getnbr("12305"),		12305);
  TEST(my_getnbr("123"),		123);
  TEST(my_getnbr("123a13"),		123);
  TEST(my_getnbr("1"),			1);
  TEST(my_getnbr("0"),			0);
  TEST(my_getnbr("00123"),		123);
  TEST(my_getnbr("-123"),		-123);
  TEST(my_getnbr("--123"),		123);
  TEST(my_getnbr("---123"),		-123);
  TEST(my_getnbr("+-123"),		-123);
  TEST(my_factorielle_rec(1),		1);
  TEST(my_factorielle_rec(2),		2);
  TEST(my_factorielle_rec(3),		6);
  TEST(my_factorielle_rec(4),		24);
  TEST(my_factorielle_rec(5),		120);
  TEST(my_factorielle_rec(0),		1);
  TEST(my_factorielle_rec(-1),		0);
  TEST(my_factorielle_it(1),		1);
  TEST(my_factorielle_it(2),		2);
  TEST(my_factorielle_it(3),		6);
  TEST(my_factorielle_it(4),		24);
  TEST(my_factorielle_it(5),		120);
  TEST(my_factorielle_it(0),		1);
  TEST(my_factorielle_it(-1),		0);
  TEST(my_power_it(10, 1),		10);
  TEST(my_power_it(10, 2),		100);
  TEST(my_power_it(10, 3),		1000);
  TEST(my_power_it(10, 0),		1);
  TEST(my_power_it(10, -1),		0);
  TEST(my_power_it(3, 3),		27);
  TEST(my_power_it(0, 3),		0);
  TEST(my_strcmp("aba", "abb"),		strcmp("aba", "abb"));
  TEST(my_strcmp("abb", "abb"),		strcmp("abb", "abb"));
  TEST(my_strcmp("abc", "abb"),		strcmp("abc", "abb"));
  TEST(my_strcmp("ab", "abb"),		strcmp("ab", "abb"));
  TEST(my_strcmp("", "ab"),		strcmp("", "ab"));
  TEST(my_strcmp("aa", ""),		strcmp("aa", ""));
  for (i = 0; i < 5; i++)
  {
    TEST(my_strncmp("aba", "abb", i),	strncmp("aba", "abb", i));
    TEST(my_strncmp("abb", "abb", i),	strncmp("abb", "abb", i));
    TEST(my_strncmp("abc", "abb", i),	strncmp("abc", "abb", i));
    TEST(my_strncmp("ab", "abb", i),	strncmp("ab", "abb", i));
    TEST(my_strncmp("", "ab", i),	strncmp("", "ab", i));
    TEST(my_strncmp("aa", "", i),	strncmp("aa", "", i));
  }
  R 0;
  (V)c;
  (V)v;
}

I main(I c,C**v)
{
  I a;
  I b;
  TEST(my_putchar('c'),			1);
  TEST(my_putchar(42),			1);
  TEST(my_strlen("toto"),		4);
  TEST(my_strlen(""),			0);
  TEST(my_putstr("toto"),		4);
  TEST(my_putstr(""),			0);
  TEST(my_aff_alpha(),			26);
  TEST(my_aff_revalpha(),		26);
  TEST(my_aff_chiffre(),		10);
  TEST(my_isneg(-1),			1);
  TEST(my_isneg(1),			1);
  TEST(my_isneg(0),			1);
  TEST(my_putnbr(1234),			4);
  TEST(my_putnbr(0),			1);
  TEST(my_putnbr(1),			1);
  TEST(my_putnbr(-1234),		5);
  TEST(my_putnbr(2147483647),		10);
  TEST(my_putnbr(-2147483647-1),	11);
  TEST(my_power_rec(10, 1),		10);
  TEST(my_power_rec(10, 2),		100);
  TEST(my_power_rec(10, 3),		1000);
  TEST(my_power_rec(10, 0),		1);
  TEST(my_power_rec(10, -1),		0);
  TEST(my_power_rec(3, 3),		27);
  TEST(my_power_rec(0, 3),		0);
  TEST(my_aff_combn(2),			178);
  TEST(my_aff_combn(3),			598);
  TEST(my_aff_comb(),			598);
  TEST(_b(0, 2, 2),			1);
  TEST(_b(0, 3, 3),			12);
  TEST(_b(0, 4, 4),			123);
  TEST(_c(120),				0);
  TEST(_c(121),				0);
  TEST(_c(122),				0);
  TEST(_c(123),				1);
  TEST(_c(124),				1);
  TEST(_c(1234),			1);
  TEST(_c(1225),			0);
  TEST(_c(1215),			0);
  a=5;
  b=3;
  TEST(my_swap(&a, &b),			0);
  TEST(PN(a) + PN(b),			2);
  R 0;
  (V)c;
  (V)v;
}
