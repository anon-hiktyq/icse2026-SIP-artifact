#include "luaT_tryconcatTM.h"
void luaT_tryconcatTMFun(void *p) 
{
    luaT_tryconcatTM *pIp = (luaT_tryconcatTM*)p;
  StkId p1 = (pIp->L)->top.p - 2;  /* first argument */
  {if (l_unlikely(callbinTM(pIp->L, s2v(p1), s2v(p1 + 1), p1, TM_CONCAT) < 0))
    {luaG_concaterror(pIp->L, s2v(p1), s2v(p1 + 1));}}
}