#include "GCTM.h"
void GCTMFun(void *p) 
{
    GCTM *pIp = (GCTM*)p;
  global_State g;{g = G(pIp->L);}
  const TValue *tm;
  TValue v;
  {lua_assert(!g->gcemergency);}
  {GCObject * udata2finalize_ret_0;IPCALL(udata2finalize,ipudata2finalize_0,.g = g,.ret = udata2finalize_ret_0);setgcovalue(pIp->L, &v, udata2finalize(g));}
  {const TValue * luaT_gettmbyobj_ret_0;IPCALL(luaT_gettmbyobj,ipluaT_gettmbyobj_0,.ret = luaT_gettmbyobj_ret_0);tm = luaT_gettmbyobj_ret_0;}
  {if (!notm(tm)) {  /* is there a finalizer? */
    TStatus status;
    lu_byte oldah = (pIp->L)->allowhook;
    lu_byte oldgcstp  = g->gcstp;
    g->gcstp |= GCSTPGC;  /* avoid GC steps */
    (pIp->L)->allowhook = 0;  /* stop debug hooks during GC metamethod */
    {setobj2s(pIp->L, pIp->L->top.p++, tm);}  /* push finalizer... */
    {setobj2s(pIp->L, pIp->L->top.p++, &v);}  /* ... and its argument */
    (pIp->L)->ci->callstatus |= CIST_FIN;  /* will run a finalizer */
    {status = luaD_pcall(pIp->L, dothecall, NULL, savestack(pIp->L, pIp->L->top.p - 2), 0);}
    (pIp->L)->ci->callstatus &= ~CIST_FIN;  /* not running a finalizer anymore */
    (pIp->L)->allowhook = oldah;  /* restore hooks */
    g->gcstp = oldgcstp;  /* restore state */
    {if (l_unlikely(status != LUA_OK)) {  /* error while running __gc? */
      {IPCALL(luaE_warnerror,ipluaE_warnerror_0);}
      (pIp->L)->top.p--;  /* pops error object */
    }}
  }}
}