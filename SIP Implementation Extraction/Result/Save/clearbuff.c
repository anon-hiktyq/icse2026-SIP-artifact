#include "clearbuff.h"
void clearbuffFun(void *p) 
{
    clearbuff *pIp = (clearbuff*)p;
  lua_State *L = pIp -> buff->L;
  const char *res;
  {TStatus luaD_rawrunprotected_ret_0;IPCALL(luaD_rawrunprotected,ipluaD_rawrunprotected_0,.ret = pIp->&luaD_rawrunprotected_ret_0);if ((luaD_rawrunprotected_ret_0)!= LUA_OK)  /* errors? */
    res = NULL;  /* error message is on the top of the stack */
  else
    res = getstr(tsvalue(s2v(L->top.p - 1)))}
  if (pIp -> buff->b != pIp -> buff->space)  /* using dynamic buffer? */
    luaM_freearray(L, pIp -> buff->b, pIp -> buff->buffsize);  /* free it */
  pIp -> ret = res;
}