#include "luaH_getshortstr.h"
void luaH_getshortstrFun(void *p) 
{
    luaH_getshortstr *pIp = (luaH_getshortstr*)p;
  const TValue * luaH_Hgetshortstr_ret_0;IPCALL(luaH_Hgetshortstr,ipluaH_Hgetshortstr_0,.t = pIp->t,.key = pIp->key,.ret = luaH_Hgetshortstr_ret_0);lu_byte finishnodeget_ret_0;IPCALL(finishnodeget,ipfinishnodeget_0,.val = luaH_Hgetshortstr_ret_0,.res = pIp->res,.ret = &finishnodeget_ret_0);*(pIp->ret) =  finishnodeget_ret_0;
}