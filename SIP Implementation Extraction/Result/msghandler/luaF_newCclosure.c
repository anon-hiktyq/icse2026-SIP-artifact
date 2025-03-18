#include "luaF_newCclosure.h"
void luaF_newCclosureFun(void *p) 
{
    luaF_newCclosure *pIp = (luaF_newCclosure*)p;
  GCObject *o;{GCObject * luaC_newobj_ret_0;IPCALL(luaC_newobj,ipluaC_newobj_0,.ret = pIp->luaC_newobj_ret_0);*o = luaC_newobj_ret_0}
  CClosure pIp -> *c = gco2ccl(o);
  pIp -> c->nupvalues = cast_byte(pIp -> nupvals);
  pIp -> ret = c;
}