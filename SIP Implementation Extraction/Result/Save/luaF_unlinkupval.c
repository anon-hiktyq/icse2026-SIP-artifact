#include "luaF_unlinkupval.h"
void luaF_unlinkupvalFun(void *p) 
{
    luaF_unlinkupval *pIp = (luaF_unlinkupval*)p;
  {lua_assert(upisopen(pIp->uv));}
  *(pIp->uv)->u.open.previous = (pIp->uv)->u.open.next;
  if ((pIp->uv)->u.open.next)
    (pIp->uv)->u.open.next->u.open.previous = (pIp->uv)->u.open.previous;
}