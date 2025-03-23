#include "luaH_psetstr.h"
void luaH_psetstrFun(void *p) 
{
    luaH_psetstr *pIp = (luaH_psetstr*)p;
  {if (strisshr(pIp->key))
    int luaH_psetshortstr_ret_0;IPCALL(luaH_psetshortstr,ipluaH_psetshortstr_0,.t = pIp->t,.key = pIp->key,.val = pIp->val,.ret = &luaH_psetshortstr_ret_0);*(pIp->ret) =  luaH_psetshortstr_ret_0;
  else
    const TValue * Hgetlongstr_ret_0;IPCALL(Hgetlongstr,ipHgetlongstr_0,.t = pIp->t,.key = pIp->key,.ret = Hgetlongstr_ret_0);int finishnodeset_ret_0;IPCALL(finishnodeset,ipfinishnodeset_0,.t = pIp->t,.slot = Hgetlongstr_ret_0,.val = pIp->val,.ret = &finishnodeset_ret_0);*(pIp->ret) =  finishnodeset_ret_0;}
}