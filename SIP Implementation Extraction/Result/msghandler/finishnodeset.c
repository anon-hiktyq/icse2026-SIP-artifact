#include "finishnodeset.h"
void finishnodesetFun(void *p) 
{
    finishnodeset *pIp = (finishnodeset*)p;
  {if (!ttisnil(pIp->slot)) {
    {setobj(((lua_State*)NULL), cast(TValue*, pIp->slot), pIp->val);}
    *(pIp->ret) =  HOK;  /* success */
  }
  else
    int retpsetcode_ret_0;IPCALL(retpsetcode,ipretpsetcode_0,.t = pIp->t,.slot = pIp->slot,.ret = &retpsetcode_ret_0);*(pIp->ret) =  retpsetcode_ret_0;}
}