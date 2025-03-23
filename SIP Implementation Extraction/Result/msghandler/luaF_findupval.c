#include "luaF_findupval.h"
void luaF_findupvalFun(void *p) 
{
    luaF_findupval *pIp = (luaF_findupval*)p;
  UpVal **pp = &(pIp->L)->openupval;
  UpVal *p;
  {lua_assert(isintwups(pIp->L) || pIp->L->openupval == NULL);}
  while ((p = *pp) != NULL && uplevel(p) >= (pIp->level)) {  /* search for it */
    {lua_assert(!isdead(G(pIp->L), p));}
    {if (uplevel(p) == pIp->level)  /* corresponding upvalue? */
      pIp->ret =  p; } /* return it */
    pp = &p->u.open.next;
  }
  /* not found: create a new upvalue after 'pp' */
  UpVal * newupval_ret_0;IPCALL(newupval,ipnewupval_0,.L = pIp->L,.level = pIp->level,.prev = pp,.ret = newupval_ret_0);pIp->ret =  newupval_ret_0;
}