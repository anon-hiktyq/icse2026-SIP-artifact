#include "setminordebt.h"
void setminordebtFun(void *p) 
{
    setminordebt *pIp = (setminordebt*)p;
  {luaE_setdebt(pIp->g, applygcparam(pIp->g, MINORMUL, pIp->g->GCmajorminor));}
}