#include "luaH_getint.h"
void luaH_getintFun(void *p) 
{
    luaH_getint *pIp = (luaH_getint*)p;
  unsigned k = ikeyinarray(pIp -> t, pIp -> key);
  if (k > 0) {
    lu_byte tag = *getArrTag(pIp -> t, k - 1);
    if (!tagisempty(tag))
      farr2val(pIp -> t, k - 1, tag, pIp -> res);
    *(pIp -> ret) = tag;
  }
  else
    *(pIp -> ret) = finishnodeget(getintfromhash(t, key), res);
}