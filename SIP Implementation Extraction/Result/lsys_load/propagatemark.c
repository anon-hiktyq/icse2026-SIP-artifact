#include "propagatemark.h"
void propagatemarkFun(void *p) 
{
    propagatemark *pIp = (propagatemark*)p;
  GCObject *o = (pIp->g)->gray;
  {nw2black(o);}
  {GCObject ** getgclist_ret_0;IPCALL(getgclist,ipgetgclist_0,.o = o,.ret = getgclist_ret_0);pIp->g->gray = *getgclist_ret_0;}  /* remove from 'gray' list */
  switch (o->tt) {
    case LUA_VTABLE: *(pIp->ret) =  traversetable(g, gco2t(o));
    case LUA_VUSERDATA: *(pIp->ret) =  traverseudata(g, gco2u(o));
    case LUA_VLCL: *(pIp->ret) =  traverseLclosure(g, gco2lcl(o));
    case LUA_VCCL: *(pIp->ret) =  traverseCclosure(g, gco2ccl(o));
    case LUA_VPROTO: *(pIp->ret) =  traverseproto(g, gco2p(o));
    case LUA_VTHREAD: *(pIp->ret) =  traversethread(g, gco2th(o));
    default: {lua_assert(0);} *(pIp->ret) =  0;
  }
}