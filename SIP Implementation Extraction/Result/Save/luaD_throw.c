#include "luaD_throw.h"
void luaD_throwFun(void *p) 
{
    luaD_throw *pIp = (luaD_throw*)p;
  if ((pIp->L)->errorJmp) {  /* thread has an error handler? */
    (pIp->L)->errorJmp->status = (pIp->errcode);  /* set status */
    {LUAI_THROW(pIp->L, pIp->L->errorJmp);}  /* jump to it */
  }
  else {  /* thread has no error handler */
    global_State g;{g = G(pIp->L);}
    lua_State mainth;{mainth = mainthread(g);}
    {TStatus luaE_resetthread_ret_0;IPCALL(luaE_resetthread,ipluaE_resetthread_0,.ret = &luaE_resetthread_ret_0);pIp->errcode = luaE_resetthread_ret_0;}  /* close all upvalues */
    (pIp->L)->status = (pIp->errcode);
    if (mainth->errorJmp) {  /* main thread has a handler? */
      {setobjs2s(pIp->L, mainth->top.p++, pIp->L->top.p - 1);}  /* copy error obj. */
      {IPCALL(luaD_throw,ipluaD_throw_0,.L = mainth,.errcode = pIp->errcode);}  /* re-throw in main thread */
    }
    else {  /* no handler at all; abort */
      if (g->panic) {  /* panic function? */
        {lua_unlock(pIp->L);}
        {int panic_ret_0;IPCALL(panic,ippanic_0,.ret = &panic_ret_0);panic_ret_0;}  /* call panic function (last chance to jump out) */
      }
      abort();
    }
  }
}