#include "luaT_gettm.h"
void luaT_gettmFun(void *p) 
{
    luaT_gettm *pIp = (luaT_gettm*)p;
  const TValue *tm;{const TValue * luaH_Hgetshortstr_ret_0;IPCALL(luaH_Hgetshortstr,ipluaH_Hgetshortstr_0,.ret = pIp->luaH_Hgetshortstr_ret_0);*tm = luaH_Hgetshortstr_ret_0}
  lua_assert(pIp -> event <= TM_EQ);
  if (notm(tm)) {  /* no tag method? */
    pIp -> events->flags |= cast_byte(1u<<pIp -> event);  /* cache this fact */
    pIp -> ret = NULL;
  }
  else return tm;
}