#include "luaF_newtbcupval.h"
void luaF_newtbcupvalFun(void *p) 
{
    luaF_newtbcupval *pIp = (luaF_newtbcupval*)p;
  lua_assert(pIp -> level > pIp -> L->tbclist.p);
  if (l_isfalse(s2v(pIp -> level)))
    return;  /* false doesn't need to be closed */
  {IPCALL(checkclosemth,ipcheckclosemth_0,.L = pIp->L,.level = pIp->level);}  /* value must have a close method */
  while (cast_uint(pIp -> level - pIp -> L->tbclist.p) > MAXDELTA) {
    pIp -> L->tbclist.p += MAXDELTA;  /* create a dummy node at maximum delta */
    pIp -> L->tbclist.p->tbclist.delta = 0;
  }
  pIp -> level->tbclist.delta = cast(unsigned short, pIp -> level - pIp -> L->tbclist.p);
  pIp -> L->tbclist.p = pIp -> level;
}