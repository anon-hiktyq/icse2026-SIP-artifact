#include "luaL_traceback.h"
void luaL_tracebackFun(void *p) 
{
    luaL_traceback *pIp = (luaL_traceback*)p;
  luaL_Buffer b;
  lua_Debug ar;
  int last;{int lastlevel_ret_0; IPCALL(lastlevel,iplastlevel_0,.L = pIp->L1,.ret = &lastlevel_ret_0);last = lastlevel_ret_0;}
  int limit2show = (last - (pIp->level) > LEVELS1 + LEVELS2) ? LEVELS1 : -1;
  {IPCALL(luaL_buffinit,ipluaL_buffinit_0,.L = pIp->L,.B = &b);}
  if ((pIp->msg)) {
    {IPCALL(luaL_addstring,ipluaL_addstring_1,.B = &b,.s = pIp->msg);}
    {luaL_addchar(&b, '\n');}
  }
  {IPCALL(luaL_addstring,ipluaL_addstring_0,.B = &b,.s = "stack traceback:");}
  while (lua_getstack((pIp->L1), (pIp->level)++, &ar)) {
    if (limit2show-- == 0) {  /* too many levels? */
      int n = last - (pIp->level) - LEVELS2 + 1;  /* number of levels to skip */
      {const char * lua_pushfstring_ret_0;IPCALL(lua_pushfstring,iplua_pushfstring_0,.ret = lua_pushfstring_ret_0);lua_pushfstring_ret_0;}
      {IPCALL(luaL_addvalue,ipluaL_addvalue_0,.B = &b);}  /* add warning about skip */
      (pIp->level) += n;  /* and skip to last levels */
    }
    else {
      {int lua_getinfo_ret_0;IPCALL(lua_getinfo,iplua_getinfo_0,.ret = &lua_getinfo_ret_0);lua_getinfo_ret_0;}
      if (ar.currentline <= 0)
        {const char * lua_pushfstring_ret_1;IPCALL(lua_pushfstring,iplua_pushfstring_1,.ret = lua_pushfstring_ret_1);lua_pushfstring_ret_1;}
      else
        {const char * lua_pushfstring_ret_2;IPCALL(lua_pushfstring,iplua_pushfstring_2,.ret = lua_pushfstring_ret_2);lua_pushfstring_ret_2;}
      {IPCALL(luaL_addvalue,ipluaL_addvalue_1,.B = &b);}
      {IPCALL(pushfuncname,ippushfuncname_0,.L = pIp->L,.ar = &ar);}
      {IPCALL(luaL_addvalue,ipluaL_addvalue_2,.B = &b);}
      if (ar.istailcall)
        {IPCALL(luaL_addstring,ipluaL_addstring_2,.B = &b,.s = "\n\t(...tail calls...)");}
    }
  }
  {IPCALL(luaL_pushresult,ipluaL_pushresult_0,.B = &b);}
}