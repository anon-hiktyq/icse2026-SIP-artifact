#include "lua_type.h"
void lua_typeFun(void *p) 
{
    lua_type *pIp = (lua_type*)p;
  const TValue o;{TValue * index2value_ret_0; IPCALL(index2value,ipindex2value_0,.L = pIp->L,.idx = pIp->idx,.ret = index2value_ret_0);o = index2value_ret_0;}
  *(pIp->ret) =  (isvalid(L, o) ? ttype(o) : LUA_TNONE);
}