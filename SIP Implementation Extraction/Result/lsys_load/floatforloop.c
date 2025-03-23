#include "floatforloop.h"
void floatforloopFun(void *p) 
{
    floatforloop *pIp = (floatforloop*)p;
  lua_Number step;{step = fltvalue(s2v(pIp->ra + 1));}
  lua_Number limit;{limit = fltvalue(s2v(pIp->ra));}
  lua_Number idx;{idx = fltvalue(s2v(pIp->ra + 2));}  /* control variable */
  {idx = luai_numadd(L, idx, step);}  /* increment index */
  {if (luai_numlt(0, step) ? luai_numle(idx, limit)
                          : luai_numle(limit, idx)) {
    {chgfltvalue(s2v(pIp->ra + 2), idx);}  /* update control variable */
    *(pIp->ret) =  1;  /* jump back */
  }
  else
    *(pIp->ret) =  0; } /* finish the loop */
}