#include "lua_getmetatable.h"
void lua_getmetatableFun(void *p) 
{
    lua_getmetatable *pIp = (lua_getmetatable*)p;
  const TValue *obj;
  Table *mt;
  int res = 0;
  {lua_lock(pIp->L);}
  {TValue * index2value_ret_0;IPCALL(index2value,ipindex2value_0,.L = pIp->L,.idx = pIp->objindex,.ret = index2value_ret_0);obj = index2value_ret_0;}
  {switch (ttype(obj)) {
    case LUA_TTABLE:
      {mt = hvalue(obj)->metatable;}
      break;
    case LUA_TUSERDATA:
      {mt = uvalue(obj)->metatable;}
      break;
    default:
      {mt = G(pIp->L)->mt[ttype(obj)];}
      break;
  }}
  if (mt != NULL) {
    {sethvalue2s(pIp->L, pIp->L->top.p, mt);}
    {api_incr_top(pIp->L);}
    res = 1;
  }
  {lua_unlock(pIp->L);}
  *(pIp->ret) =  res;
}