#include "traverseproto.h"
void traverseprotoFun(void *p) 
{
    traverseproto *pIp = (traverseproto*)p;
  int i;
  markobjectN(pIp -> g, pIp -> f->source);
  for (i = 0; i < pIp -> f->sizek; i++)  /* mark literals */
    {IPCALL(reallymarkobject,ipreallymarkobject_1,.g = pIp->g,.o = &f->k[i]);}
  for (i = 0; i < pIp -> f->sizeupvalues; i++)  /* mark upvalue names */
    markobjectN(pIp -> g, pIp -> f->upvalues[i].name);
  for (i = 0; i < pIp -> f->sizep; i++)  /* mark nested protos */
    {IPCALL(reallymarkobject,ipreallymarkobject_0,.g = pIp->g,.o = f->p[i]);}
  for (i = 0; i < pIp -> f->sizelocvars; i++)  /* mark local-variable names */
    markobjectN(pIp -> g, pIp -> f->locvars[i].varname);
  *(pIp -> ret) = 1 + f->sizek + f->sizeupvalues + f->sizep + f->sizelocvars;
}