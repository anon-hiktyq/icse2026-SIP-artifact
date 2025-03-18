#include "lua_setfield.h"
void lua_setfieldFun(void *p) 
{
    lua_setfield *pIp = (lua_setfield*)p;
  lua_lock(pIp -> L);  /* unlock done in 'auxsetstr' */
  {TValue * index2value_ret_0;IPCALL(index2value,ipindex2value_0,.L = pIp->L,.idx = pIp->idx,.ret = index2value_ret_0);IPCALL(auxsetstr,ipauxsetstr_0,.L = pIp->L,.t = index2value_ret_0,.k = pIp->k);}
}