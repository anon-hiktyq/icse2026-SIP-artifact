#include "luaG_opinterror.h"
void luaG_opinterrorFun(void *p) 
{
    luaG_opinterror *pIp = (luaG_opinterror*)p;
  {if (!ttisnumber(pIp->p1))  /* first operand is wrong? */
    (pIp->p2) = (pIp->p1); } /* now second is wrong */
  {IPCALL(luaG_typeerror,ipluaG_typeerror_0,.L = pIp->L,.o = pIp->p2,.op = pIp->msg);}
}