
#include "newhint.h"

/*@
  requires \valid(pIp);
  requires \valid(pIp->t);
  requires \valid(lenhint(pIp->t));
  requires \valid(pIp->ret);
  requires pIp->hint <= pIp->t->asize;
  assigns *lenhint(pIp->t), *(pIp->ret);
  ensures *lenhint(pIp->t) == \old(pIp->hint);
  ensures *(pIp->ret) == \old(pIp->hint);
*/
void newhintFun(newhint* pIp) 
{
  lua_assert(pIp -> hint <= pIp -> t->asize);
  *lenhint(pIp -> t) = pIp -> hint;
  *(pIp -> ret) = pIp->hint;
}
