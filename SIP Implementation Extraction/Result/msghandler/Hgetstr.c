#include "Hgetstr.h"
void HgetstrFun(void *p) 
{
    Hgetstr *pIp = (Hgetstr*)p;
  {if (strisshr(pIp->key))
    const TValue * luaH_Hgetshortstr_ret_0;IPCALL(luaH_Hgetshortstr,ipluaH_Hgetshortstr_0,.t = pIp->t,.key = pIp->key,.ret = luaH_Hgetshortstr_ret_0);pIp->ret =  luaH_Hgetshortstr_ret_0;
  else
    const TValue * Hgetlongstr_ret_0;IPCALL(Hgetlongstr,ipHgetlongstr_0,.t = pIp->t,.key = pIp->key,.ret = Hgetlongstr_ret_0);pIp->ret =  Hgetlongstr_ret_0;}
}