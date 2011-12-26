#define C(B,E,S)(1+(E)*2+(B)*4+(((B)/2)*2)*(((B)+1)/2))
__(int $,int o,int O,int Q,char c){return $<(C(Q-1,Q+3,
Q)-O-1)/2?(write(1," ",1)+__(++$,o,O,Q,c)):(o<O?write(1
,&c,1)+__($,++o,O,Q,c):write(1,"\n",1));}_(int or,int e
,int $,int o,int Q){return or<Q?(e<or+4?__(0,0,C(or,e,Q
),Q,'*')+_(or,++e,0,0,Q):_(++or,0,0,0,Q)):e<Q?__(0,0,Q|
1,Q,'|')+_(or,++e,0,0,Q):0;}main(int c,char **v){return
c>1&&atoi(1[v])>=0?_(0,0,0,0,atoi(1[v])):0;}
