#include "propagateall.h"
void propagateallFun(void *p) 
{
    propagateall *pIp = (propagateall*)p;
  while ((pIp->g)->gray)
    {l_mem propagatemark_ret_0;IPCALL(propagatemark,ippropagatemark_0,.g = pIp->g,.ret = &propagatemark_ret_0);propagatemark_ret_0;}
}