#include "gettable.h"
void gettableFun(void *p) 
{
    gettable *pIp = (gettable*)p;
  TValue *t;{TValue * index2value_ret_0;IPCALL(index2value,ipindex2value_0,.L = pIp->L,.idx = pIp->idx,.ret = pIp->index2value_ret_0);*t = index2value_ret_0}
  api_check(pIp -> L, ttistable(t), "table expected");
  pIp -> ret = hvalue(t);
}