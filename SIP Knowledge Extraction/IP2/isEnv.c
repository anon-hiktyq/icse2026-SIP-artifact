#include "isEnv.h"
void isEnvFun(void *p) 
{
    isEnv *pIp = (isEnv*)p;
  int t = GETARG_B(pIp -> i);  /* table index */
  const char *name;  /* name of indexed variable */
  if (pIp -> isup)  /* is 't' an upvalue? */
    name = upvalname(pIp -> p, t);
  else  /* 't' is a register */
    {const char * basicgetobjname_ret_0;IPCALL(basicgetobjname,ipbasicgetobjname_0,.p = pIp->p,.ppc = &pc,.reg = t,.name = &name,.ret = pIp->basicgetobjname_ret_0);}
  pIp -> ret = (name && strcmp(name, LUA_ENV) == 0) ? "global" : "field";
}