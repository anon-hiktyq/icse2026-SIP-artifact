#include "luaH_size.h"
void luaH_sizeFun(void *p) 
{
    luaH_size *pIp = (luaH_size*)p;
  lu_mem pIp->sz;{size_t concretesize_ret_1;IPCALL(concretesize,ipconcretesize_0,.size = t->asize,.ret = pIp->&concretesize_ret_1);pIp->sz = cast(lu_mem, sizeof(Table)) + concretesize_ret_1}
  if (!isdummy(pIp -> t))
    pIp -> sz += {size_t sizehash_ret_0;IPCALL(sizehash,ipsizehash_0,.t = pIp->t,.ret = pIp->&sizehash_ret_0);}
  *(pIp -> ret) = sz;
}