#include "traverseudata.h"
void traverseudataFun(void *p) 
{
    traverseudata *pIp = (traverseudata*)p;
  int i;
  markobjectN(pIp -> g, pIp -> u->metatable);  /* mark its metatable */
  for (i = 0; i < pIp -> u->nuvalue; i++)
    {IPCALL(reallymarkobject,ipreallymarkobject_0,.g = pIp->g,.o = &u->uv[i].uv);}
  {IPCALL(genlink,ipgenlink_0,.pIp->g = pIp->pIp->g,.o = obj2gco(pIp->u));}
  *(pIp -> ret) = 1 + u->nuvalue;
}