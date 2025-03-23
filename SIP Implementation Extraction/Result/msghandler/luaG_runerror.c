#include "luaG_runerror.h"
void luaG_runerrorFun(void *p) 
{
    luaG_runerror *pIp = (luaG_runerror*)p;
  CallInfo *ci = (pIp->L)->ci;
  const char *msg;
  va_list argp;
  {luaC_checkGC(pIp->L);}  /* error message uses memory */
  va_start(argp, (pIp->fmt));
  {const char * luaO_pushvfstring_ret_0;IPCALL(luaO_pushvfstring,ipluaO_pushvfstring_0,.ret = luaO_pushvfstring_ret_0);msg = luaO_pushvfstring_ret_0;}  /* format message */
  va_end(argp);
  if (msg == NULL)  /* no memory to format message? */
    {IPCALL(luaD_throw,ipluaD_throw_0);}
  else {if (isLua(ci)) {  /* Lua function? */
    /* add source:line information */
    {luaG_addinfo(pIp->L, msg, ci_func(ci)->p->source, getcurrentline(ci));}
    {setobjs2s(pIp->L, pIp->L->top.p - 2, pIp->L->top.p - 1);}  /* remove 'msg' */
    (pIp->L)->top.p--;
  }}
  {IPCALL(luaG_errormsg,ipluaG_errormsg_0,.L = pIp->L);}
}