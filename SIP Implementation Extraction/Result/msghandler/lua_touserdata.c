#include "lua_touserdata.h"
void lua_touserdataFun(void *p) 
{
    lua_touserdata *pIp = (lua_touserdata*)p;
  const TValue o;{TValue * index2value_ret_0; IPCALL(index2value,ipindex2value_0,.L = pIp->L,.idx = pIp->idx,.ret = index2value_ret_0);o = index2value_ret_0;}
  void * touserdata_ret_0;IPCALL(touserdata,iptouserdata_0,.o = o,.ret = touserdata_ret_0);pIp->ret =  touserdata_ret_0;
}