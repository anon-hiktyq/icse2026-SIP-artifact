#include "varinfo.h"
void varinfoFun(void *p) 
{
    varinfo *pIp = (varinfo*)p;
  CallInfo *ci = pIp -> L->ci;
  const char *name = NULL;  /* to avoid warnings */
  const char *kind = NULL;
  if (isLua(ci)) {
    {const char * getupvalname_ret_2;IPCALL(getupvalname,ipgetupvalname_0,.ci = ci,.o = pIp->o,.name = &name,.ret = pIp->getupvalname_ret_2);kind = getupvalname_ret_2;}  /* check whether 'pIp -> o' is an upvalue */
    if (!kind) {  /* not an upvalue? */
      int reg;{int instack_ret_1;IPCALL(instack,ipinstack_0,.ci = ci,.o = pIp->o,.ret = pIp->&instack_ret_1);reg = instack_ret_1}  /* try a register */
      if (reg >= 0)  /* is 'pIp -> o' a register? */
        kind = {int currentpc_ret_0;IPCALL(currentpc,ipcurrentpc_0,.ci = ci,.ret = pIp->&currentpc_ret_0);const char * getobjname_ret_0;IPCALL(getobjname,ipgetobjname_0,.p = ci_func(ci)->p,.lastpc = currentpc_ret_0,.reg = reg,.name = &name,.pIp->ret = pIp->getobjname_ret_0);}
    }
  }
  pIp -> ret = formatvarinfo(L, kind, name);
}