#include "lua_setmetatable.h"
void lua_setmetatableFun(void *p) 
{
    lua_setmetatable *pIp = (lua_setmetatable*)p;
  TValue *obj;
  Table *mt;
  {lua_lock(pIp->L);}
  {api_checkpop(pIp->L, 1);}
  {TValue * index2value_ret_0;IPCALL(index2value,ipindex2value_0,.L = pIp->L,.idx = pIp->objindex,.ret = index2value_ret_0);obj = index2value_ret_0;}
  {if (ttisnil(s2v(pIp->L->top.p - 1)))
    mt = NULL;
  else {
    {api_check(pIp->L, ttistable(s2v(pIp->L->top.p - 1)), "table expected");}
    {mt = hvalue(s2v(pIp->L->top.p - 1));}
  }}
  {switch (ttype(obj)) {
    case LUA_TTABLE: {
      {hvalue(obj)->metatable = mt;}
      if (mt) {
        {luaC_objbarrier(pIp->L, gcvalue(obj), mt);}
        {luaC_checkfinalizer(pIp->L, gcvalue(obj), mt);}
      }
      break;
    }
    case LUA_TUSERDATA: {
      {uvalue(obj)->metatable = mt;}
      if (mt) {
        {luaC_objbarrier(pIp->L, uvalue(obj), mt);}
        {luaC_checkfinalizer(pIp->L, gcvalue(obj), mt);}
      }
      break;
    }
    default: {
      {G(pIp->L)->mt[ttype(obj)] = mt;}
      break;
    }
  }}
  (pIp->L)->top.p--;
  {lua_unlock(pIp->L);}
  *(pIp->ret) =  1;
}