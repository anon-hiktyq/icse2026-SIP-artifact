#include "hashkeyisempty.h"
void hashkeyisemptyFun(void *p) 
{
    hashkeyisempty *pIp = (hashkeyisempty*)p;
  const TValue val;{val = getintfromhash(pIp->t, l_castU2S(pIp->key));}
  *(pIp->ret) =  isempty(val);
}