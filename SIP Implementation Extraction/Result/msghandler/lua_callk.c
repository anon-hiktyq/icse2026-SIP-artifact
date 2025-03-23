#include "lua_callk.h"
void lua_callkFun(void *p) 
{
    lua_callk *pIp = (lua_callk*)p;
  StkId func;
  {lua_lock(pIp->L);}
  {api_check(pIp->L, pIp->k == NULL || !isLua(pIp->L->ci),
    "cannot use continuations inside hooks");}
  {api_checkpop(pIp->L, pIp->nargs + 1);}
  {api_check(pIp->L, pIp->L->status == LUA_OK, "cannot do calls on non-normal thread");}
  {checkresults(pIp->L, pIp->nargs, pIp->nresults);}
  func = (pIp->L)->top.p - ((pIp->nargs)+1);
  {if (pIp->k != NULL && yieldable(pIp->L)) {  /* need to prepare continuation? */
    (pIp->L)->ci->u.c.k = (pIp->k);  /* save continuation */
    (pIp->L)->ci->u.c.ctx = (pIp->ctx);  /* save context */
    {IPCALL(luaD_call,ipluaD_call_0);}  /* do the call */
  }
  else  /* no continuation or no yieldable */
    {IPCALL(luaD_callnoyield,ipluaD_callnoyield_0);}}  /* just do the call */
  {adjustresults(pIp->L, pIp->nresults);}
  {lua_unlock(pIp->L);}
}