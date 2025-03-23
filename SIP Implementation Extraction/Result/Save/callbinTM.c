#include "callbinTM.h"
void callbinTMFun(void *p) 
{
    callbinTM *pIp = (callbinTM*)p;
  const TValue tm;{const TValue * luaT_gettmbyobj_ret_1; IPCALL(luaT_gettmbyobj,ipluaT_gettmbyobj_1,.L = pIp->L,.o = pIp->p1,.event = pIp->event,.ret = luaT_gettmbyobj_ret_1);tm = luaT_gettmbyobj_ret_1;}  /* try first operand */
  {if (notm(tm))
    {const TValue * luaT_gettmbyobj_ret_0;IPCALL(luaT_gettmbyobj,ipluaT_gettmbyobj_0,.L = pIp->L,.o = pIp->p2,.event = pIp->event,.ret = luaT_gettmbyobj_ret_0);tm = luaT_gettmbyobj_ret_0;}}  /* try second operand */
  {if (notm(tm))
    *(pIp->ret) =  -1;  /* tag method not found */
  else  /* call tag method and return the tag of the result */
    lu_byte luaT_callTMres_ret_0;IPCALL(luaT_callTMres,ipluaT_callTMres_0,.L = pIp->L,.f = tm,.p1 = pIp->p1,.p2 = pIp->p2,.res = pIp->res,.ret = &luaT_callTMres_ret_0);*(pIp->ret) =  luaT_callTMres_ret_0;}
}