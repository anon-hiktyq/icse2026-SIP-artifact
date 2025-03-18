#include "propagatemark.h"
void propagatemarkFun(void *p) 
{
    propagatemark *pIp = (propagatemark*)p;
  GCObject *o = pIp -> g->gray;
  nw2black(o);
  {GCObject ** getgclist_ret_6;IPCALL(getgclist,ipgetgclist_0,.o = o,.ret = pIp->getgclist_ret_6);pIp->g->gray = *getgclist_ret_6;}  /* remove from 'gray' list */
  switch (o->tt) {
    case LUA_VTABLE: return {l_mem traversetable_ret_5;IPCALL(traversetable,iptraversetable_0,.pIp->g = pIp->pIp->g,.h = gco2t(o),.pIp->ret = pIp->&traversetable_ret_5);}
    case LUA_VUSERDATA: return {l_mem traverseudata_ret_4;IPCALL(traverseudata,iptraverseudata_0,.pIp->g = pIp->pIp->g,.u = gco2u(o),.pIp->ret = pIp->&traverseudata_ret_4);}
    case LUA_VLCL: return {l_mem traverseLclosure_ret_3;IPCALL(traverseLclosure,iptraverseLclosure_0,.pIp->g = pIp->pIp->g,.cl = gco2lcl(o),.pIp->ret = pIp->&traverseLclosure_ret_3);}
    case LUA_VCCL: return {l_mem traverseCclosure_ret_2;IPCALL(traverseCclosure,iptraverseCclosure_0,.pIp->g = pIp->pIp->g,.cl = gco2ccl(o),.pIp->ret = pIp->&traverseCclosure_ret_2);}
    case LUA_VPROTO: return {l_mem traverseproto_ret_1;IPCALL(traverseproto,iptraverseproto_0,.pIp->g = pIp->pIp->g,.f = gco2p(o),.pIp->ret = pIp->&traverseproto_ret_1);}
    case LUA_VTHREAD: return {l_mem traversethread_ret_0;IPCALL(traversethread,iptraversethread_0,.pIp->g = pIp->pIp->g,.th = gco2th(o),.pIp->ret = pIp->&traversethread_ret_0);}
    default: lua_assert(0); return 0;
  }
}