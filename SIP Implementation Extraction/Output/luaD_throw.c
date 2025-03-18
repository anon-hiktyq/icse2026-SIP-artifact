#include "luaD_throw.h"
void luaD_throwFun(void *p) 
{
    luaD_throw *pIp = (luaD_throw*)p;
  if (pIp -> L->errorJmp) {  /* thread has an error handler? */
    pIp -> L->errorJmp->status = pIp -> errcode;  /* set status */
    LUAI_THROW(pIp -> L, pIp -> L->errorJmp);  /* jump to it */
  }
  else {  /* thread has no error handler */
    global_State *g = G(pIp -> L);
    lua_State *mainth = mainthread(g);
    pIp -> errcode = luaE_resetthread(pIp -> L, pIp -> errcode);  /* close all upvalues */
    pIp -> L->status = pIp -> errcode;
    if (mainth->errorJmp) {  /* main thread has a handler? */
      setobjs2s(pIp -> L, mainth->top.p++, pIp -> L->top.p - 1);  /* copy error obj. */
      luaD_throw(mainth, pIp -> errcode);  /* re-throw in main thread */
    }
    else {  /* no handler at all; abort */
      if (g->panic) {  /* panic function? */
        lua_unlock(pIp -> L);
        g->panic(pIp -> L);  /* call panic function (last chance to jump out) */
      }
      abort();
    }
  }
}