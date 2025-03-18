#include "luaT_gettmbyobj.h"
void luaT_gettmbyobjFun(void *p) 
{
    luaT_gettmbyobj *pIp = (luaT_gettmbyobj*)p;
  Table *mt;
  switch (ttype(pIp -> o)) {
    case LUA_TTABLE:
      mt = hvalue(pIp -> o)->metatable;
      break;
    case LUA_TUSERDATA:
      mt = uvalue(pIp -> o)->metatable;
      break;
    default:
      mt = G(pIp -> L)->mt[ttype(pIp -> o)];
  }
  pIp -> ret = (mt ? luaH_Hgetshortstr(mt, G(L)->tmname[event]) : &G(L)->nilvalue);
}