#include "pushfuncname.h"
void pushfuncnameFun(void *p) 
{
    pushfuncname *pIp = (pushfuncname*)p;
  {int pushglobalfuncname_ret_1;IPCALL(pushglobalfuncname,ippushglobalfuncname_0,.L = pIp->L,.ar = pIp->ar,.ret = &pushglobalfuncname_ret_1);if ((pushglobalfuncname_ret_1) {  /* try first a global name */
    {const char * lua_pushfstring_ret_0;IPCALL(lua_pushfstring,iplua_pushfstring_0,.ret = lua_pushfstring_ret_0);}
    {IPCALL(lua_settop,iplua_settop_0);lua_remove(pIp->L, -2);}  /* remove name */
  }
  else if (pIp -> *ar->namewhat != '\0')  /* is there a name from code? */
    lua_pushfstring(pIp -> L, "%s '%s'", pIp -> ar->namewhat, pIp -> ar->name);  /* use it */
  else if (pIp -> *ar->what == 'm')  /* main? */
      lua_pushliteral(pIp -> L, "main chunk");
  else if (pIp -> *ar->what != 'C')  /* for Lua functions, use <file:line> */
    lua_pushfstring(pIp -> L, "function <%s:%d>", pIp -> ar->short_src, pIp -> ar->linedefined);
  else  /* nothing left... */
    lua_pushliteral(pIp -> L, "?")}
}