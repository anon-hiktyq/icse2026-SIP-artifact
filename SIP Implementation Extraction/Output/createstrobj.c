#include "createstrobj.h"
void createstrobjFun(void *p) 
{
    createstrobj *pIp = (createstrobj*)p;

  TString *ts;
  GCObject *o;
  {GCObject * luaC_newobj_ret_0;IPCALL(luaC_newobj,ipluaC_newobj_0,.ret = pIp->luaC_newobj_ret_0);o = luaC_newobj_ret_0;}
  ts = gco2ts(o);
  ts->hash = pIp -> h;
  ts->extra = 0;
  pIp -> ret = ts;
}