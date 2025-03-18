#include "callclosemethod.h"
void callclosemethodFun(void *p) 
{
    callclosemethod *pIp = (callclosemethod*)p;
  StkId top = pIp -> L->top.p;
  StkId func = top;
  const TValue *tm;{const TValue * luaT_gettmbyobj_ret_0;IPCALL(luaT_gettmbyobj,ipluaT_gettmbyobj_0,.ret = luaT_gettmbyobj_ret_0);*tm = luaT_gettmbyobj_ret_0}
  setobj2s(pIp -> L, top++, tm);  /* will call metamethod... */
  setobj2s(pIp -> L, top++, pIp -> obj);  /* with 'self' as the 1st argument */
  if (pIp -> err != NULL)  /* if there was an error... */
    setobj2s(pIp -> L, top++, pIp -> err);  /* then error object will be 2nd argument */
  pIp -> L->top.p = top;  /* add function and arguments */
  if (pIp -> yy)
    luaD_call(pIp -> L, func, 0);
  else
    {IPCALL(luaD_callnoyield,ipluaD_callnoyield_0);}
}