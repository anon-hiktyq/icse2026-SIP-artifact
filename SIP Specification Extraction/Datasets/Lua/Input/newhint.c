#include "newhint.h"
void newhintFun(newhint* pIp) 
{
  lua_assert(pIp -> hint <= pIp -> t->asize);
  *lenhint(pIp -> t) = pIp -> hint;
  *(pIp -> ret) = pIp->hint;
}