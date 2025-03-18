#include "luaH_psetstr.h"
void luaH_psetstrFun(void *p) 
{
    luaH_psetstr *pIp = (luaH_psetstr*)p;
  if (strisshr(pIp -> key))
    *(pIp -> ret) = luaH_psetshortstr(t, key, val);
  else
    *(pIp -{const TValue * Hgetlongstr_ret_0;IPCALL(Hgetlongstr,ipHgetlongstr_0,.t = pIp->t,.key = pIp->key,.ret = pIp->Hgetlongstr_ret_0);int finishnodeset_ret_0;IPCALL(finishnodeset,ipfinishnodeset_0,.t = pIp->t,.slot = Hgetlongstr_ret_0,.val = pIp->val,.ret = pIp->&finishnodeset_ret_0);}y), val);
}