#include "luaH_getint.h"
void luaH_getintFun(void *p) 
{
    luaH_getint *pIp = (luaH_getint*)p;
  unsigned k;{k = ikeyinarray(pIp->t, pIp->key);}
  if (k > 0) {
    lu_byte tag;{tag = *getArrTag(pIp->t, k - 1);}
    {if (!tagisempty(tag))
      {farr2val(pIp->t, k - 1, tag, pIp->res);}}
    *(pIp->ret) =  tag;
  }
  else
    const TValue * getintfromhash_ret_0;IPCALL(getintfromhash,ipgetintfromhash_0,.t = pIp->t,.key = pIp->key,.ret = getintfromhash_ret_0);lu_byte finishnodeget_ret_0;IPCALL(finishnodeget,ipfinishnodeget_0,.val = getintfromhash_ret_0,.res = pIp->res,.ret = &finishnodeget_ret_0);*(pIp->ret) =  finishnodeget_ret_0;
}