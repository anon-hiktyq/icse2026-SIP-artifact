#include "luaH_new.h"
void luaH_newFun(void *p) 
{
    luaH_new *pIp = (luaH_new*)p;
  GCObject *o;{GCObject * luaC_newobj_ret_0;IPCALL(luaC_newobj,ipluaC_newobj_0,.ret = pIp->luaC_newobj_ret_0);*o = luaC_newobj_ret_0}
  Table pIp -> *t = gco2t(o);
  pIp -> t->metatable = NULL;
  pIp -> t->flags = maskflags;  /* table has no metamethod fields */
  pIp -> t->array = NULL;
  pIp -> t->asize = 0;
  {IPCALL(setnodevector,ipsetnodevector_0,.L = pIp->L,.t = pIp->t,.size = 0);}
  pIp -> ret = t;
}