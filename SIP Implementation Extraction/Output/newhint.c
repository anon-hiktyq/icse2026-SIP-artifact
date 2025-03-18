#include "newhint.h"
void newhintFun(void *p) 
{
    newhint *pIp = (newhint*)p;
  lua_assert(pIp -> hint <= pIp -> t->asize);
  *lenhint(pIp -> t) = pIp -> hint;
  *(pIp -> ret) = hint;
}