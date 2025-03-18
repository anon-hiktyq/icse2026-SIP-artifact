#include "luaG_runerror.h"
void luaG_runerrorFun(void *p) 
{
    luaG_runerror *pIp = (luaG_runerror*)p;
  CallInfo *ci = pIp -> L->ci;
  const char *msg;
  va_list argp;
  luaC_checkGC(pIp -> L);  /* error message uses memory */
  va_start(argp, pIp -> fmt);
  {const char * luaO_pushvfstring_ret_1;IPCALL(luaO_pushvfstring,ipluaO_pushvfstring_0,.ret = luaO_pushvfstring_ret_1);msg = luaO_pushvfstring_ret_1;}  /* format message */
  va_end(argp);
  if (msg == NULL)  /* no memory to format message? */
    luaD_throw(pIp -> L, LUA_ERRMEM);
  else if (isLua(ci)) {  /* Lua function? */
    /* add source:line information */
    {int getcurrentline_ret_0;IPCALL(getcurrentline,ipgetcurrentline_0,.ci = ci,.ret = &getcurrentline_ret_0);const char * luaG_addinfo_ret_0;IPCALL(luaG_addinfo,ipluaG_addinfo_0,.pIp->L = pIp->pIp->L,.msg = msg,.src = ci_func(ci)->p->source,.line = getcurrentline_ret_0,.ret = luaG_addinfo_ret_0);}
    setobjs2s(pIp -> L, pIp -> L->top.p - 2, pIp -> L->top.p - 1);  /* remove 'msg' */
    pIp -> L->top.p--;
  }
  {IPCALL(luaG_errormsg,ipluaG_errormsg_0,.L = pIp->L);}
}