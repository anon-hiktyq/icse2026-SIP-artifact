#include "traversestrongtable.h"
void traversestrongtableFun(void *p) 
{
    traversestrongtable *pIp = (traversestrongtable*)p;
  Node limit;{limit = gnodelast(pIp->h);}
  {int traversearray_ret_0;IPCALL(traversearray,iptraversearray_0,.g = pIp->g,.h = pIp->h,.ret = &traversearray_ret_0);traversearray_ret_0;}
  for (n = gnode((pIp->h), 0); n < limit; n++) {  /* traverse hash part */
    {if (isempty(gval(n)))  /* entry is empty? */
      {IPCALL(clearkey,ipclearkey_0,.n = n);}  /* clear its key */
    else {
      {lua_assert(!keyisnil(n));}
      {markkey(pIp->g, n);}
      {markvalue(pIp->g, gval(n));}
    }}
  }
  {genlink(pIp->g, obj2gco(pIp->h));}
}