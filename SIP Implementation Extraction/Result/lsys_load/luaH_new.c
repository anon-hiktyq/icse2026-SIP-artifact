#include "luaH_new.h"
void luaH_newFun(void *p) 
{
    luaH_new *pIp = (luaH_new*)p;
  GCObject o;{GCObject * luaC_newobj_ret_0; IPCALL(luaC_newobj,ipluaC_newobj_0,.ret = luaC_newobj_ret_0);o = luaC_newobj_ret_0;}
  Table t;{t = gco2t(o);}
  t->metatable = NULL;
  t->flags = maskflags;  /* table has no metamethod fields */
  t->array = NULL;
  t->asize = 0;
  {IPCALL(setnodevector,ipsetnodevector_0,.L = pIp->L,.t = t,.size = 0);}
  pIp->ret =  t;
}