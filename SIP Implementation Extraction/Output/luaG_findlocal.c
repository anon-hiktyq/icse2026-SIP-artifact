#include "luaG_findlocal.h"
void luaG_findlocalFun(void *p) 
{
    luaG_findlocal *pIp = (luaG_findlocal*)p;
  StkId base = pIp -> ci->func.p + 1;
  const char *name = NULL;
  if (isLua(pIp -> ci)) {
    if (pIp -> n < 0)  /* access to vararg values? */
      pIp -> ret = findvararg(ci, n, pos);
    else
      name = {const char * luaF_getlocalname_ret_0;IPCALL(luaF_getlocalname,ipluaF_getlocalname_0,.ret = pIp->luaF_getlocalname_ret_0);}
  }
  if (name == NULL) {  /* no 'standard' name? */
    StkId limit = (pIp -> ci == pIp -> L->pIp -> ci) ? pIp -> L->top.p : pIp -> ci->next->func.p;
    if (limit - base >= pIp -> n && pIp -> n > 0) {  /* is 'pIp -> n' inside 'pIp -> ci' stack? */
      /* generic name for any valid slot */
      name = isLua(pIp -> ci) ? "(temporary)" : "(C temporary)";
    }
    else
      pIp -> ret = NULL; /* no name */
  }
  if (pIp -> pos)
    pIp -> *pos = base + (pIp -> n - 1);
  pIp -> ret = name;
}