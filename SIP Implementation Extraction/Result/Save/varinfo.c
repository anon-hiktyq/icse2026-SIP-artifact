#include "varinfo.h"
void varinfoFun(void *p) 
{
    varinfo *pIp = (varinfo*)p;
  CallInfo *ci = (pIp->L)->ci;
  const char *name = NULL;  /* to avoid warnings */
  const char *kind = NULL;
  {if (isLua(ci)) {
    {const char * getupvalname_ret_0;IPCALL(getupvalname,ipgetupvalname_0,.ci = ci,.o = pIp->o,.name = &name,.ret = getupvalname_ret_0);kind = getupvalname_ret_0;}  /* check whether 'o' is an upvalue */
    if (!kind) {  /* not an upvalue? */
      int reg;{int instack_ret_0; IPCALL(instack,ipinstack_0,.ci = ci,.o = pIp->o,.ret = &instack_ret_0);reg = instack_ret_0;}  /* try a register */
      if (reg >= 0)  /* is 'o' a register? */
        {kind = getobjname(ci_func(ci)->p, currentpc(ci), reg, &name);}
    }
  }}
  const char * formatvarinfo_ret_0;IPCALL(formatvarinfo,ipformatvarinfo_0,.L = pIp->L,.kind = kind,.name = name,.ret = formatvarinfo_ret_0);pIp->ret =  formatvarinfo_ret_0;
}