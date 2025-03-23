#include "luaG_findlocal.h"
void luaG_findlocalFun(void *p) 
{
    luaG_findlocal *pIp = (luaG_findlocal*)p;
  StkId base = (pIp->ci)->func.p + 1;
  const char *name = NULL;
  {if (isLua(pIp->ci)) {
    if ((pIp->n) < 0)  /* access to vararg values? */
      const char * findvararg_ret_0;IPCALL(findvararg,ipfindvararg_0,.ci = pIp->ci,.n = pIp->n,.pos = pIp->pos,.ret = findvararg_ret_0);pIp->ret =  findvararg_ret_0;
    else
      {name = luaF_getlocalname(ci_func(pIp->ci)->p, pIp->n, currentpc(pIp->ci));}
  }}
  if (name == NULL) {  /* no 'standard' name? */
    StkId limit = ((pIp->ci) == (pIp->L)->ci) ? (pIp->L)->top.p : (pIp->ci)->next->func.p;
    if (limit - base >= (pIp->n) && (pIp->n) > 0) {  /* is 'n' inside 'ci' stack? */
      /* generic name for any valid slot */
      {name = isLua(pIp->ci) ? "(temporary)" : "(C temporary)";}
    }
    else
      pIp->ret =  NULL;  /* no name */
  }
  if ((pIp->pos))
    *(pIp->pos) = base + ((pIp->n) - 1);
  pIp->ret =  name;
}