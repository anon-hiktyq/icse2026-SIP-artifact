#include "luaF_newLclosure.h"
void luaF_newLclosureFun(void *p) 
{
    luaF_newLclosure *pIp = (luaF_newLclosure*)p;
  GCObject *o;{GCObject * luaC_newobj_ret_0;IPCALL(luaC_newobj,ipluaC_newobj_0,.ret = pIp->luaC_newobj_ret_0);*o = luaC_newobj_ret_0}
  LClosure pIp -> *c = gco2lcl(o);
  pIp -> c->p = NULL;
  pIp -> c->nupvalues = cast_byte(pIp -> nupvals);
  while pIp -> (nupvals--) c->upvals[pIp -> nupvals] = NULL;
  pIp -> ret = c;
}