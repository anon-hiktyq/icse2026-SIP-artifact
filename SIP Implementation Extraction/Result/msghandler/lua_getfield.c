#include "lua_getfield.h"
void lua_getfieldFun(void *p) 
{
    lua_getfield *pIp = (lua_getfield*)p;
  lua_lock(pIp -> L);
  *(pIp -> ret) = auxgetstr(L, index2value(L, idx), k);
}