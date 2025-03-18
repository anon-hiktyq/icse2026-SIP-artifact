#include "hashkeyisempty.h"
void hashkeyisemptyFun(void *p) 
{
    hashkeyisempty *pIp = (hashkeyisempty*)p;
  const TValue *val;{const TValue * getintfromhash_ret_0;IPCALL(getintfromhash,ipgetintfromhash_0,.pIp->t = pIp->pIp->t,.pIp->key = pIp->l_castU2S(pIp->key),.pIp->ret = pIp->getintfromhash_ret_0);*val = getintfromhash_ret_0}
  *(pIp -> ret) = isempty(val);
}