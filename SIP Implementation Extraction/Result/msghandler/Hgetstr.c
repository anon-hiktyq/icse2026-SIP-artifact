#include "Hgetstr.h"
void HgetstrFun(void *p) 
{
    Hgetstr *pIp = (Hgetstr*)p;
  if (strisshr(pIp -> key))
    pIp -> ret = luaH_Hgetshortstr(t, key);
  else
    pIp -> {const TValue * Hgetlongstr_ret_0;IPCALL(Hgetlongstr,ipHgetlongstr_0,.t = pIp->t,.key = pIp->key,.ret = pIp->Hgetlongstr_ret_0);} key);
}