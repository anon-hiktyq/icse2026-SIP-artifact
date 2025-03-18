#include "traversestrongtable.h"
void traversestrongtableFun(void *p) 
{
    traversestrongtable *pIp = (traversestrongtable*)p;
  Node *n, *limit = gnodelast(pIp -> h);
  {int traversearray_ret_0;IPCALL(traversearray,iptraversearray_0,.g = pIp->g,.h = pIp->h,.ret = &traversearray_ret_0);}
  for (n = gnode(pIp -> h, 0); n < limit; n++) {  /* traverse hash part */
    if (isempty(gval(n)))  /* entry is empty? */
      clearkey(n);  /* clear its key */
    else {
      lua_assert(!keyisnil(n));
      markkey(pIp -> g, n);
      {IPCALL(reallymarkobject,ipreallymarkobject_0,.pIp->g = pIp->pIp->g,.o = gval(n));}
    }
  }
  {IPCALL(genlink,ipgenlink_0,.pIp->g = pIp->pIp->g,.o = obj2gco(pIp->h));}
}