#include "luaS_newudata.h"
void luaS_newudataFun(void *p) 
{
    luaS_newudata *pIp = (luaS_newudata*)p;
  Udata pIp -> *u;
  int i;
  GCObject *o;
  if (l_unlikely(pIp -> s > MAX_SIZE - udatamemoffset(pIp -> nuvalue)))
    {IPCALL(luaM_toobig,ipluaM_toobig_0);}
  {GCObject * luaC_newobj_ret_0;IPCALL(luaC_newobj,ipluaC_newobj_0,.ret = pIp->luaC_newobj_ret_0);o = luaC_newobj_ret_0;}
  pIp -> u = gco2u(o);
  pIp -> u->len = pIp -> s;
  pIp -> u->pIp -> nuvalue = pIp -> nuvalue;
  pIp -> u->metatable = NULL;
  for (i = 0; i < pIp -> nuvalue; i++)
    setnilvalue(pIp -> &u->uv[i].uv);
  pIp -> ret = u;
}