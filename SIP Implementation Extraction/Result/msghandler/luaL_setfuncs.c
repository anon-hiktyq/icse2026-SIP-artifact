#include "luaL_setfuncs.h"
void luaL_setfuncsFun(void *p) 
{
    luaL_setfuncs *pIp = (luaL_setfuncs*)p;
  {IPCALL(luaL_checkstack,ipluaL_checkstack_0,.L = pIp->L,.space = nup,.msg = "too many upvalues");}
  for (; pIp -> l->name != NULL; pIp -> l++) {  /* fill the table with given functions */
    if (pIp -> l->func == NULL)  /* placeholder? */
      lua_pushboolean(pIp -> L, 0);
    else {
      int i;
      for (i = 0; i < pIp -> nup; i++)  /* copy upvalues to the top */
        {IPCALL(lua_pushvalue,iplua_pushvalue_0);}
      {IPCALL(lua_pushcclosure,iplua_pushcclosure_0);}  /* closure with those upvalues */
    }
    {IPCALL(lua_setfield,iplua_setfield_0);}
  }
  lua_pop(pIp -> L, pIp -> nup);  /* remove upvalues */
}