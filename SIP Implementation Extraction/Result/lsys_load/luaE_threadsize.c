#include "luaE_threadsize.h"
void luaE_threadsizeFun(void *p) 
{
    luaE_threadsize *pIp = (luaE_threadsize*)p;
  lu_mem sz;{sz = cast(lu_mem, sizeof(LX))
            + cast_uint(pIp->L->nci) * sizeof(CallInfo);}
  if ((pIp->L)->stack.p != NULL)
    {sz += cast_uint(stacksize(pIp->L) + EXTRA_STACK) * sizeof(StackValue);}
  *(pIp->ret) =  sz;
}