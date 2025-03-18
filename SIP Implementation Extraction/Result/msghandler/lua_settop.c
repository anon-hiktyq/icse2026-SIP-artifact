#include "lua_settop.h"
void lua_settopFun(void *p) 
{
    lua_settop *pIp = (lua_settop*)p;
  CallInfo *ci;
  StkId func, newtop;
  ptrdiff_t diff;  /* difference for new top */
  lua_lock(pIp -> L);
  ci = pIp -> L->ci;
  func = ci->func.p;
  if (pIp -> idx >= 0) {
    api_check(pIp -> L, pIp -> idx <= ci->top.p - (func + 1), "new top too large");
    diff = ((func + 1) + pIp -> idx) - pIp -> L->top.p;
    for (; diff > 0; diff--)
      setnilvalue(s2v(pIp -> L->top.p++));  /* clear new slots */
  }
  else {
    api_check(pIp -> L, -(pIp -> idx+1) <= (pIp -> L->top.p - (func + 1)), "invalid new top");
    diff = pIp -> idx + 1;  /* will "subtract" index (as it is negative) */
  }
  newtop = pIp -> L->top.p + diff;
  if (diff < 0 && pIp -> L->tbclist.p >= newtop) {
    lua_assert(ci->callstatus & CIST_TBC);
    {StkId luaF_close_ret_0;IPCALL(luaF_close,ipluaF_close_0,.ret = &luaF_close_ret_0);newtop = luaF_close_ret_0;}
  }
  pIp -> L->top.p = newtop;  /* correct top only after closing any upvalue */
  lua_unlock(pIp -> L);
}