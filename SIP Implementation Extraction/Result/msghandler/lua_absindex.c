#include "lua_absindex.h"
void lua_absindexFun(void *p) 
{
    lua_absindex *pIp = (lua_absindex*)p;
  return (pIp -> idx > 0 || ispseudo(pIp -> idx))
         ? pIp -> idx
         : cast_int(pIp -> L->top.p - pIp -> L->ci->func.p) + pIp -> idx;
}