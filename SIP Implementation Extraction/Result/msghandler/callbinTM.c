#include "callbinTM.h"
void callbinTMFun(void *p) 
{
    callbinTM *pIp = (callbinTM*)p;

  const TValue *tm;{const TValue * luaT_gettmbyobj_ret_2;IPCALL(luaT_gettmbyobj,ipluaT_gettmbyobj_1,.L = pIp->L,.o = p1,.event = pIp->event,.ret = pIp->luaT_gettmbyobj_ret_2);*tm = luaT_gettmbyobj_ret_2}  /* try first operand */
  if (notm(tm))
    tm = {const TValue * luaT_gettmbyobj_ret_1;IPCALL(luaT_gettmbyobj,ipluaT_gettmbyobj_0,.L = pIp->L,.o = p2,.event = pIp->event,.ret = pIp->luaT_gettmbyobj_ret_1);}  /* try second operand */
  if (notm(tm))
    *(pIp -> ret) = -1; /* tag method not found */
  else  /* call tag method and return the tag of the result */
    *(pIp -{lu_byte luaT_callTMres_ret_0;IPCALL(luaT_callTMres,ipluaT_callTMres_0,.L = pIp->L,.f = tm,.p1 = pIp->p1,.p2 = pIp->p2,.res = pIp->res,.ret = pIp->&luaT_callTMres_ret_0);}p2, res);
}