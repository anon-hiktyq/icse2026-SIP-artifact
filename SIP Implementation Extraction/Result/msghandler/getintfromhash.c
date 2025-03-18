#include "getintfromhash.h"
void getintfromhashFun(void *p) 
{
    getintfromhash *pIp = (getintfromhash*)p;
  Node *n;{Node * hashint_ret_0;IPCALL(hashint,iphashint_0,.t = pIp->t,.i = key,.ret = pIp->hashint_ret_0);*n = hashint_ret_0}
  lua_assert(!ikeyinarray(pIp -> t, pIp -> key));
  for (;;) {  /* check whether 'pIp -> key' is somewhere in the chain */
    if (keyisinteger(n) && keyival(n) == pIp -> key)
      pIp -> ret = gval(n); /* that's it */
    else {
      int nx = gnext(n);
      if (nx == 0) break;
      n += nx;
    }
  }
  pIp -> ret = &absentkey;
}