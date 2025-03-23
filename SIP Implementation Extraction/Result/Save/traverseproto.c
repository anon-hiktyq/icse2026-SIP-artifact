#include "traverseproto.h"
void traverseprotoFun(void *p) 
{
    traverseproto *pIp = (traverseproto*)p;
  int i;
  {markobjectN(pIp->g, pIp->f->source);}
  for (i = 0; i < (pIp->f)->sizek; i++)  /* mark literals */
    {markvalue(pIp->g, &pIp->f->k[i]);}
  for (i = 0; i < (pIp->f)->sizeupvalues; i++)  /* mark upvalue names */
    {markobjectN(pIp->g, pIp->f->upvalues[i].name);}
  for (i = 0; i < (pIp->f)->sizep; i++)  /* mark nested protos */
    {markobjectN(pIp->g, pIp->f->p[i]);}
  for (i = 0; i < (pIp->f)->sizelocvars; i++)  /* mark local-variable names */
    {markobjectN(pIp->g, pIp->f->locvars[i].varname);}
  *(pIp->ret) =  1 + (pIp->f)->sizek + (pIp->f)->sizeupvalues + (pIp->f)->sizep + (pIp->f)->sizelocvars;
}