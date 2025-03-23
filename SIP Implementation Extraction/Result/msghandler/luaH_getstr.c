#include "luaH_getstr.h"
void luaH_getstrFun(void *p) 
{
    luaH_getstr *pIp = (luaH_getstr*)p;
  const TValue * Hgetstr_ret_0;IPCALL(Hgetstr,ipHgetstr_0,.t = pIp->t,.key = pIp->key,.ret = Hgetstr_ret_0);lu_byte finishnodeget_ret_0;IPCALL(finishnodeget,ipfinishnodeget_0,.val = Hgetstr_ret_0,.res = pIp->res,.ret = &finishnodeget_ret_0);*(pIp->ret) =  finishnodeget_ret_0;
}