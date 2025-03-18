#include "luaD_hookcall.h"
void luaD_hookcallFun(void *p) 
{
    luaD_hookcall *pIp = (luaD_hookcall*)p;
  pIp -> L->oldpc = 0;  /* set 'oldpc' for new function */
  if (pIp -> L->hookmask & LUA_MASKCALL) {  /* is call hook on? */
    int event = (pIp -> ci->callstatus & CIST_TAIL) ? LUA_HOOKTAILCALL
                                             : LUA_HOOKCALL;
    Proto *p = ci_func(pIp -> ci)->p;
    pIp -> ci->u.l.savedpc++;  /* hooks assume 'pc' is already incremented */
    {IPCALL(luaD_hook,ipluaD_hook_0,.L = pIp->L,.event = event,.line = -1,.ftransfer = 1,.ntransfer = p->numparams);}
    pIp -> ci->u.l.savedpc--;  /* correct 'pc' */
  }
}