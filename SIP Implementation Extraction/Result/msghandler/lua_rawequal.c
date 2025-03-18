#include "lua_rawequal.h"
void lua_rawequalFun(void *p) 
{
    lua_rawequal *pIp = (lua_rawequal*)p;
  const TValue *o1;{TValue * index2value_ret_1;IPCALL(index2value,ipindex2value_1,.L = pIp->L,.idx = index1,.ret = pIp->index2value_ret_1);*o1 = index2value_ret_1}
  const TValue *o2;{TValue * index2value_ret_0;IPCALL(index2value,ipindex2value_0,.L = pIp->L,.idx = index2,.ret = pIp->index2value_ret_0);*o2 = index2value_ret_0}
  *(pIp -> ret) = (isvalid(L, o1) && isvalid(L, o2)) ? luaV_rawequalobj(o1, o2) : 0;
}