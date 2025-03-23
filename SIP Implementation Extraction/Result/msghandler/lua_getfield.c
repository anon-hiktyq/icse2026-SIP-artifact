#include "lua_getfield.h"
void lua_getfieldFun(void *p) 
{
    lua_getfield *pIp = (lua_getfield*)p;
  {lua_lock(pIp->L);}
  TValue * index2value_ret_0;IPCALL(index2value,ipindex2value_0,.L = pIp->L,.idx = pIp->idx,.ret = index2value_ret_0);int auxgetstr_ret_0;IPCALL(auxgetstr,ipauxgetstr_0,.L = pIp->L,.t = index2value_ret_0,.k = pIp->k,.ret = &auxgetstr_ret_0);*(pIp->ret) =  auxgetstr_ret_0;
}