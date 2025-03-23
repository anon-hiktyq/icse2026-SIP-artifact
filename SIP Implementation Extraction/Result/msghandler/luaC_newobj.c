#include "luaC_newobj.h"
void luaC_newobjFun(void *p) 
{
    luaC_newobj *pIp = (luaC_newobj*)p;
  GCObject * luaC_newobjdt_ret_0;IPCALL(luaC_newobjdt,ipluaC_newobjdt_0,.L = pIp->L,.tt = pIp->tt,.sz = pIp->sz,.offset = 0,.ret = luaC_newobjdt_ret_0);pIp->ret =  luaC_newobjdt_ret_0;
}