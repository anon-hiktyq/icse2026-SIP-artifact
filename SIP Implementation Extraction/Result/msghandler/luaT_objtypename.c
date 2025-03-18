#include "luaT_objtypename.h"
void luaT_objtypenameFun(void *p) 
{
    luaT_objtypename *pIp = (luaT_objtypename*)p;
  Table *mt;
  if ((ttistable(pIp -> o) && (mt = hvalue(pIp -> o)->metatable) != NULL) ||
      (ttisfulluserdata(pIp -> o) && (mt = uvalue(pIp -> o)->metatable) != NULL)) {
    const TValue *name;{const TValue * luaH_Hgetshortstr_ret_0;IPCALL(luaH_Hgetshortstr,ipluaH_Hgetshortstr_0,.ret = pIp->luaH_Hgetshortstr_ret_0);*name = luaH_Hgetshortstr_ret_0}
    if (ttisstring(name))  /* is '__name' a string? */
      pIp -> ret = getstr(tsvalue(name)); /* use it as type name */
  }
  pIp -> ret = ttypename(ttype(o)); /* else use standard type name */
}