#include "newupval.h"
void newupvalFun(void *p) 
{
    newupval *pIp = (newupval*)p;
  GCObject *o;{GCObject * luaC_newobj_ret_0;IPCALL(luaC_newobj,ipluaC_newobj_0,.ret = pIp->luaC_newobj_ret_0);*o = luaC_newobj_ret_0}
  UpVal pIp -> *uv = gco2upv(o);
  UpVal *next = pIp -> *prev;
  pIp -> uv->v.p = s2v(pIp -> level);  /* current value lives in the stack */
  pIp -> uv->u.open.next = next;  /* link it to list of open upvalues */
  pIp -> uv->u.open.previous = pIp -> prev;
  if (next)
    next->u.open.previous = pIp -> &uv->u.open.next;
  pIp -> *prev = pIp -> uv;
  if (!isintwups(pIp -> L)) {  /* thread not in list of threads with upvalues? */
    pIp -> L->twups = G(pIp -> L)->twups;  /* link it to the list */
    G(pIp -> L)->twups = pIp -> L;
  }
  pIp -> ret = uv;
}