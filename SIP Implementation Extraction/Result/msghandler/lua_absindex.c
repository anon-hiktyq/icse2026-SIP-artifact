#include "lua_absindex.h"
void lua_absindexFun(void *p) 
{
    lua_absindex *pIp = (lua_absindex*)p;
  *(pIp->ret) =  (idx > 0 || ispseudo(idx))
         ? idx
         : cast_int(L->top.p - L->ci->func.p) + idx;
}