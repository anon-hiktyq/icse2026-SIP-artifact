#include "getintfromhash.h"
void getintfromhashFun(void *p) 
{
    getintfromhash *pIp = (getintfromhash*)p;
  Node n;{Node * hashint_ret_0; IPCALL(hashint,iphashint_0,.t = pIp->t,.i = pIp->key,.ret = hashint_ret_0);n = hashint_ret_0;}
  {lua_assert(!ikeyinarray(pIp->t, pIp->key));}
  for (;;) {  /* check whether 'key' is somewhere in the chain */
    {if (keyisinteger(n) && keyival(n) == pIp->key)
      pIp->ret =  gval(n);  /* that's it */
    else {
      int nx;{nx = gnext(n);}
      if (nx == 0) break;
      n += nx;
    }}
  }
  pIp->ret =  &absentkey;
}