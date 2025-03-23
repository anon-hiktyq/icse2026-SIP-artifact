#include "luaT_callTMres.h"
void luaT_callTMresFun(void *p) 
{
    luaT_callTMres *pIp = (luaT_callTMres*)p;
  ptrdiff_t result;{result = savestack(pIp->L, pIp->res);}
  StkId func = (pIp->L)->top.p;
  {setobj2s(pIp->L, func, pIp->f);}  /* push function (assume EXTRA_STACK) */
  {setobj2s(pIp->L, func + 1, pIp->p1);}  /* 1st argument */
  {setobj2s(pIp->L, func + 2, pIp->p2);}  /* 2nd argument */
  (pIp->L)->top.p += 3;
  /* metamethod may yield only when called from Lua code */
  {if (isLuacode(pIp->L->ci))
    {IPCALL(luaD_call,ipluaD_call_0);}
  else
    {IPCALL(luaD_callnoyield,ipluaD_callnoyield_0);}}
  {pIp->res = restorestack(pIp->L, result);}
  {setobjs2s(pIp->L, pIp->res, --pIp->L->top.p);}  /* move result to its place */
  *(pIp->ret) =  ttypetag(s2v(res));  /* return tag of the result */
}