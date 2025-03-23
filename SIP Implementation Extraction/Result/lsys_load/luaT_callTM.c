#include "luaT_callTM.h"
void luaT_callTMFun(void *p) 
{
    luaT_callTM *pIp = (luaT_callTM*)p;
  StkId func = (pIp->L)->top.p;
  {setobj2s(pIp->L, func, pIp->f);}  /* push function (assume EXTRA_STACK) */
  {setobj2s(pIp->L, func + 1, pIp->p1);}  /* 1st argument */
  {setobj2s(pIp->L, func + 2, pIp->p2);}  /* 2nd argument */
  {setobj2s(pIp->L, func + 3, pIp->p3);}  /* 3rd argument */
  (pIp->L)->top.p = func + 4;
  /* metamethod may yield only when called from Lua code */
  {if (isLuacode(pIp->L->ci))
    {IPCALL(luaD_call,ipluaD_call_0);}
  else
    {IPCALL(luaD_callnoyield,ipluaD_callnoyield_0);}}
}