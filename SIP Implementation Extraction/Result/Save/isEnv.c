#include "isEnv.h"
void isEnvFun(void *p) 
{
    isEnv *pIp = (isEnv*)p;
  int t;{t = GETARG_B(pIp->i);}  /* table index */
  const char *name;  /* name of indexed variable */
  if ((pIp->isup))  /* is 't' an upvalue? */
    {const char * upvalname_ret_0;IPCALL(upvalname,ipupvalname_0,.p = pIp->p,.uv = t,.ret = upvalname_ret_0);name = upvalname_ret_0;}
  else  /* 't' is a register */
    {const char * basicgetobjname_ret_0;IPCALL(basicgetobjname,ipbasicgetobjname_0,.p = pIp->p,.ppc = &pc,.reg = t,.name = &name,.ret = basicgetobjname_ret_0);basicgetobjname_ret_0;}
  pIp->ret =  (name && strcmp(name, LUA_ENV) == 0) ? "global" : "field";
}