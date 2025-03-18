#include "findindex.h"
void findindexFun(void *p) 
{
    findindex *pIp = (findindex*)p;

  unsigned int i;
  if (ttisnil(pIp -> key)) return 0;  /* first iteration */
  {unsigned int keyinarray_ret_1;IPCALL(keyinarray,ipkeyinarray_0,.t = pIp->t,.key = pIp->key,.ret = pIp->&keyinarray_ret_1);i = keyinarray_ret_1;}
  if (i != 0)  /* is 'pIp -> key' inside array part? */
    *(pIp -> ret) = i; /* yes; that's the index */
  else {
    const TValue *n;{const TValue * getgeneric_ret_0;IPCALL(getgeneric,ipgetgeneric_0,.t = pIp->t,.key = pIp->key,.deadok = 1,.ret = pIp->getgeneric_ret_0);*n = getgeneric_ret_0}
    if (l_unlikely(isabstkey(n)))
      {IPCALL(luaG_runerror,ipluaG_runerror_0);}  /* pIp -> key not found */
    i = cast_uint(nodefromval(n) - gnode(pIp -> t, 0));  /* pIp -> key index in hash table */
    /* hash elements are numbered after array ones */
    *(pIp -> ret) = (i + 1) + asize;
  }
}