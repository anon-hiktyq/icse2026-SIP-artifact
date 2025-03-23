#include "luaL_pushresult.h"
void luaL_pushresultFun(void *p) 
{
    luaL_pushresult *pIp = (luaL_pushresult*)p;
  lua_State *L = (pIp->B)->L;
  {checkbufferlevel(pIp->B, -1);}
  {if (!buffonstack(pIp->B))  /* using static buffer? */
    {const char * lua_pushlstring_ret_0;IPCALL(lua_pushlstring,iplua_pushlstring_0,.ret = lua_pushlstring_ret_0);lua_pushlstring_ret_0;}  /* save result as regular string */
  else {  /* reuse buffer already allocated */
    UBox box;{void * lua_touserdata_ret_0; IPCALL(lua_touserdata,iplua_touserdata_0,.ret = lua_touserdata_ret_0);box = (UBox *)lua_touserdata_ret_0;}
    void *ud;
    lua_Alloc allocf;{lua_Alloc lua_getallocf_ret_0; IPCALL(lua_getallocf,iplua_getallocf_0,.ret = &lua_getallocf_ret_0);allocf = lua_getallocf_ret_0;}  /* function to free buffer */
    size_t len = (pIp->B)->n;  /* final string length */
    char *s;
    {void * resizebox_ret_0;IPCALL(resizebox,ipresizebox_0,.L = L,.idx = -1,.newsize = len + 1,.ret = resizebox_ret_0);resizebox_ret_0;}  /* adjust box size to content size */
    s = (char*)box->box;  /* final buffer address */
    s[len] = '\0';  /* add ending zero */
    /* clear box, as Lua will take control of the buffer */
    box->bsize = 0;  box->box = NULL;
    {const char * lua_pushexternalstring_ret_0;IPCALL(lua_pushexternalstring,iplua_pushexternalstring_0,.ret = lua_pushexternalstring_ret_0);lua_pushexternalstring_ret_0;}
    {IPCALL(lua_closeslot,iplua_closeslot_0);}  /* close the box */
    {int lua_gc_ret_0;IPCALL(lua_gc,iplua_gc_0,.ret = &lua_gc_ret_0);lua_gc_ret_0;}
  }}
  {lua_remove(L, -2);}  /* remove box or placeholder from the stack */
}