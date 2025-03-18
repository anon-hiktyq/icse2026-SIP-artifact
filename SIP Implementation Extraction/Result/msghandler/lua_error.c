#include "lua_error.h"
void lua_errorFun(void *p) 
{
    lua_error *pIp = (lua_error*)p;
  TValue *errobj;
  lua_lock(pIp -> L);
  errobj = s2v(pIp -> L->top.p - 1);
  api_checkpop(pIp -> L, 1);
  /* error object is the memory error message? */
  if (ttisshrstring(errobj) && eqshrstr(tsvalue(errobj), G(pIp -> L)->memerrmsg))
    luaM_error(pIp -> L);  /* raise a memory error */
  else
    {IPCALL(luaG_errormsg,ipluaG_errormsg_0);}  /* raise a regular error */
  /* code unreachable; will unlock when control actually leaves the kernel */
  *(pIp -> ret) = 0; /* to avoid warnings */
}