#include "sizehash.h"
void sizehashFun(void *p) 
{
    sizehash *pIp = (sizehash*)p;
  *(pIp->ret) =  cast_sizet(sizenode(t)) * sizeof(Node) + extraLastfree(t);
}