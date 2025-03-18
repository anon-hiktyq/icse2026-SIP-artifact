#include "luaD_hook.h"
void luaD_hookFun(void *p) 
{
    luaD_hook *pIp = (luaD_hook*)p;

  lua_Hook hook = pIp -> L->hook;
  if (hook && pIp -> L->allowhook) {  /* make sure there is a hook */
    CallInfo *ci = pIp -> L->ci;
    ptrdiff_t top = savestack(pIp -> L, pIp -> L->top.p);  /* preserve original 'top' */
    ptrdiff_t ci_top = savestack(pIp -> L, ci->top.p);  /* idem for 'ci->top' */
    lua_Debug ar;
    ar.pIp -> event = pIp -> event;
    ar.currentline = pIp -> line;
    ar.i_ci = ci;
    pIp -> L->transferinfo.pIp -> ftransfer = pIp -> ftransfer;
    pIp -> L->transferinfo.pIp -> ntransfer = pIp -> ntransfer;
    if (isLua(ci) && pIp -> L->top.p < ci->top.p)
      pIp -> L->top.p = ci->top.p;  /* protect entire activation register */
    luaD_checkstack(pIp -> L, LUA_MINSTACK);  /* ensure minimum stack size */
    if (ci->top.p < pIp -> L->top.p + LUA_MINSTACK)
      ci->top.p = pIp -> L->top.p + LUA_MINSTACK;
    pIp -> L->allowhook = 0;  /* cannot call hooks inside a hook */
    ci->callstatus |= CIST_HOOKED;
    lua_unlock(pIp -> L);
    (*hook)(pIp -> L, &ar);
    lua_lock(pIp -> L);
    lua_assert(!pIp -> L->allowhook);
    pIp -> L->allowhook = 1;
    ci->top.p = restorestack(pIp -> L, ci_top);
    pIp -> L->top.p = restorestack(pIp -> L, top);
    ci->callstatus &= ~CIST_HOOKED;
  }
}