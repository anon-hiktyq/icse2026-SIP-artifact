#include "pushfuncname.h"
void pushfuncnameFun(void *p) 
{
    pushfuncname *pIp = (pushfuncname*)p;
  {int pushglobalfuncname_ret_0;IPCALL(pushglobalfuncname,ippushglobalfuncname_0,.L = pIp->L,.ar = pIp->ar,.ret = &pushglobalfuncname_ret_0);if (pushglobalfuncname_ret_0) {  /* try first a global name */
    {lua_pushfstring(pIp->L, "function '%s'", lua_tostring(pIp->L, -1));}
    {lua_remove(pIp->L, -2);}  /* remove name */
  }
  else if (*(pIp->ar)->namewhat != '\0')  /* is there a name from code? */
    {const char * lua_pushfstring_ret_0;IPCALL(lua_pushfstring,iplua_pushfstring_0,.ret = lua_pushfstring_ret_0);lua_pushfstring_ret_0;}  /* use it */
  else if (*(pIp->ar)->what == 'm')  /* main? */
      {lua_pushliteral(pIp->L, "main chunk");}
  else if (*(pIp->ar)->what != 'C')  /* for Lua functions, use <file:line> */
    {const char * lua_pushfstring_ret_1;IPCALL(lua_pushfstring,iplua_pushfstring_1,.ret = lua_pushfstring_ret_1);lua_pushfstring_ret_1;}
  else  /* nothing left... */
    {lua_pushliteral(pIp->L, "?");}}
}