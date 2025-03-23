#include "traverseudata.h"
void traverseudataFun(void *p) 
{
    traverseudata *pIp = (traverseudata*)p;
  int i;
  {markobjectN(pIp->g, pIp->u->metatable);}  /* mark its metatable */
  for (i = 0; i < (pIp->u)->nuvalue; i++)
    {markvalue(pIp->g, &pIp->u->uv[i].uv);}
  {genlink(pIp->g, obj2gco(pIp->u));}
  *(pIp->ret) =  1 + (pIp->u)->nuvalue;
}