#include "traverseLclosure.h"
void traverseLclosureFun(void *p) 
{
    traverseLclosure *pIp = (traverseLclosure*)p;
  int i;
  markobjectN(pIp -> g, pIp -> cl->p);  /* mark its prototype */
  for (i = 0; i < pIp -> cl->nupvalues; i++) {  /* visit its upvalues */
    UpVal *uv = pIp -> cl->upvals[i];
    {IPCALL(reallymarkobject,ipreallymarkobject_0,.g = pIp->g,.o = uv);}  /* mark upvalue */
  }
  *(pIp -> ret) = 1 + cl->nupvalues;
}