#include "luaH_size.h"
void luaH_sizeFun(void *p) 
{
    luaH_size *pIp = (luaH_size*)p;
  lu_mem sz;{size_t concretesize_ret_0; IPCALL(concretesize,ipconcretesize_0,.size = t->asize,.ret = &concretesize_ret_0);sz = cast(lu_mem, sizeof(Table)) + concretesize_ret_0;}
  {if (!isdummy(pIp->t))
    {size_t sizehash_ret_0;IPCALL(sizehash,ipsizehash_0,.t = pIp->t,.ret = &sizehash_ret_0);sz += sizehash_ret_0;}}
  *(pIp->ret) =  sz;
}