#include "luaD_rawrunprotected.h"
void luaD_rawrunprotectedFun(void *p) 
{
    luaD_rawrunprotected *pIp = (luaD_rawrunprotected*)p;
  l_uint32 oldnCcalls = pIp -> L->nCcalls;
  struct lua_longjmp lj;
  lj.status = LUA_OK;
  lj.previous = pIp -> L->errorJmp;  /* chain new error handler */
  pIp -> L->errorJmp = &lj;
  LUAI_TRY(pIp -> L, &lj, pIp -> f, pIp -> ud);  /* call 'pIp -> f' catching errors */
  pIp -> L->errorJmp = lj.previous;  /* restore old error handler */
  pIp -> L->nCcalls = oldnCcalls;
  *(pIp -> ret) = lj.status;
}