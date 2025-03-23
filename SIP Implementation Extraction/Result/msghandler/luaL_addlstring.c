#include "luaL_addlstring.h"
void luaL_addlstringFun(void *p) 
{
    luaL_addlstring *pIp = (luaL_addlstring*)p;
  if ((pIp->l) > 0) {  /* avoid 'memcpy' when 's' can be NULL */
    char b;{char * prepbuffsize_ret_0; IPCALL(prepbuffsize,ipprepbuffsize_0,.B = pIp->B,.sz = pIp->l,.boxidx = -1,.ret = prepbuffsize_ret_0);b = prepbuffsize_ret_0;}
    memcpy(b, (pIp->s), (pIp->l) * sizeof(char));
    {luaL_addsize(pIp->B, pIp->l);}
  }
}