#include "findfield.h"
void findfieldFun(void *p) 
{
    findfield *pIp = (findfield*)p;
  {if (pIp->level == 0 || !lua_istable(pIp->L, -1))
    *(pIp->ret) =  0; } /* not found */
  {IPCALL(lua_pushnil,iplua_pushnil_0);}  /* start 'next' loop */
  while (lua_next((pIp->L), -2)) {  /* for each pair in table */
    {int lua_type_ret_0;IPCALL(lua_type,iplua_type_0,.ret = &lua_type_ret_0);if (lua_type_ret_0 == LUA_TSTRING) {  /* ignore non-string keys */
      {int lua_rawequal_ret_0;IPCALL(lua_rawequal,iplua_rawequal_0,.ret = &lua_rawequal_ret_0);if (lua_rawequal_ret_0) {  /* found object? */
        {lua_pop(pIp->L, 1);}  /* remove value (but keep name) */
        *(pIp->ret) =  1;
      }
      else {int findfield_ret_0;IPCALL(findfield,ipfindfield_0,.L = pIp->L,.objidx = pIp->objidx,.level = level - 1,.ret = &findfield_ret_0);if (findfield_ret_0) {  /* try recursively */
        /* stack: lib_name, lib_table, field_name (top) */
        {lua_pushliteral(pIp->L, ".");}  /* place '.' between the two names */
        {lua_replace(pIp->L, -3);}  /* (in the slot occupied by table) */
        {IPCALL(lua_concat,iplua_concat_0);}  /* lib_name.field_name */
        *(pIp->ret) =  1;
      }}}
    }}
    {lua_pop(pIp->L, 1);}  /* remove value */
  }
  *(pIp->ret) =  0;  /* not found */
}