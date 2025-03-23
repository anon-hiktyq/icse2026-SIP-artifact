#include "l_hashfloat.h"
void l_hashfloatFun(void *p) 
{
    l_hashfloat *pIp = (l_hashfloat*)p;
  int i;
  lua_Integer ni;
  {pIp->n = l_mathop(frexp)(pIp->n, &i) * -cast_num(INT_MIN);}
  {if (!lua_numbertointeger(pIp->n, &ni)) {  /* is 'n' inf/-inf/NaN? */
    {lua_assert(luai_numisnan(pIp->n) || l_mathop(fabs)(pIp->n) == cast_num(HUGE_VAL));}
    *(pIp->ret) =  0;
  }
  else {  /* normal case */
    unsigned int u;{u = cast_uint(i) + cast_uint(ni);}
    *(pIp->ret) =  (u <= cast_uint(INT_MAX) ? u : ~u);
  }}
}