#include "luaF_findupval.h"
void luaF_findupvalFun(void *p) 
{
    luaF_findupval *pIp = (luaF_findupval*)p;
  UpVal **pp = pIp -> &L->openupval;
  UpVal *p;
  lua_assert(isintwups(pIp -> L) || pIp -> L->openupval == NULL);
  while ((p = *pp) != NULL && uplevel(p) >= pIp -> level) {  /* search for it */
    lua_assert(!isdead(G(pIp -> L), p));
    if (uplevel(p) == pIp -> level)  /* corresponding upvalue? */
      pIp -> ret = p; /* return it */
    pp = &p->u.open.next;
  }
  /* not found: create a new upvalue after 'pp' */
  pIp -> ret = newupval(L, level, pp);
}