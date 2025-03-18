#include "createstrobj.h"
void createstrobjFun(void *p) 
{
    createstrobj *pIp = (createstrobj*)p;

  TString pIp -> *ts;
  GCObject *o;
  {GCObject * luaC_newobj_ret_0;IPCALL(luaC_newobj,ipluaC_newobj_0,.ret = pIp->luaC_newobj_ret_0);o = luaC_newobj_ret_0;}
  pIp -> ts = gco2ts(o);
  pIp -> ts->hash = pIp -> h;
  pIp -> ts->extra = 0;
  pIp -> ret = ts;
}