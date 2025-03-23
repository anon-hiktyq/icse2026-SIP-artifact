#include "luaS_newudata.h"
void luaS_newudataFun(void *p) 
{
    luaS_newudata *pIp = (luaS_newudata*)p;
  Udata *u;
  int i;
  GCObject *o;
  {if (l_unlikely(pIp->s > MAX_SIZE - udatamemoffset(pIp->nuvalue)))
    {IPCALL(luaM_toobig,ipluaM_toobig_0);}}
  {o = luaC_newobj(pIp->L, LUA_VUSERDATA, sizeudata(pIp->nuvalue, pIp->s));}
  {u = gco2u(o);}
  u->len = (pIp->s);
  u->nuvalue = (pIp->nuvalue);
  u->metatable = NULL;
  for (i = 0; i < (pIp->nuvalue); i++)
    {setnilvalue(&u->uv[i].uv);}
  pIp->ret =  u;
}