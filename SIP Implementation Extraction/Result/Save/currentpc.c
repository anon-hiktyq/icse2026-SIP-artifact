#include "currentpc.h"
void currentpcFun(void *p) 
{
    currentpc *pIp = (currentpc*)p;
  lua_assert(isLua(pIp -> ci));
  *(pIp -> ret) = pcRel(ci->u.l.savedpc, ci_func(ci)->p);
}