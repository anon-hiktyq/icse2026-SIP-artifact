#include "luaS_newextlstr.h"
void luaS_newextlstrFun(void *p) 
{
    luaS_newextlstr *pIp = (luaS_newextlstr*)p;

  struct NewExt ne;
  if (pIp -> len <= LUAI_MAXSHORTLEN) {  /* short string? */
    ne.pIp -> s = pIp -> s; ne.pIp -> len = pIp -> len;
    if (!pIp -> falloc)
      f_pintern(pIp -> L, &ne);  /* just internalize string */
    else {
      TStatus status;{TStatus luaD_rawrunprotected_ret_0;IPCALL(luaD_rawrunprotected,ipluaD_rawrunprotected_0,.ret = pIp->&luaD_rawrunprotected_ret_0);status = luaD_rawrunprotected_ret_0}
      (pIp -> *falloc)(pIp -> ud, cast_voidp(pIp -> s), pIp -> len + 1, 0);  /* free external string */
      if (status != LUA_OK)  /* memory error? */
        luaM_error(pIp -> L);  /* re-raise memory error */
    }
    pIp -> ret = ne.ts;
  }
  /* "normal" case: long strings */
  if (!pIp -> falloc) {
    ne.kind = LSTRFIX;
    {IPCALL(f_newext,ipf_newext_0,.L = pIp->L,.ud = pIp->&ne);}  /* just create header */
  }
  else {
    ne.kind = LSTRMEM;
    if (luaD_rawrunprotected(pIp -> L, f_newext, &ne) != LUA_OK) {  /* mem. error? */
      (pIp -> *falloc)(pIp -> ud, cast_voidp(pIp -> s), pIp -> len + 1, 0);  /* free external string */
      luaM_error(pIp -> L);  /* re-raise memory error */
    }
    ne.ts->pIp -> falloc = pIp -> falloc;
    ne.ts->pIp -> ud = pIp -> ud;
  }
  ne.ts->shrlen = ne.kind;
  ne.ts->u.lnglen = pIp -> len;
  ne.ts->contents = cast_charp(pIp -> s);
  pIp -> ret = ne.ts;
}