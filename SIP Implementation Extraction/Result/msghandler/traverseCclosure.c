#include "traverseCclosure.h"
void traverseCclosureFun(void *p) 
{
    traverseCclosure *pIp = (traverseCclosure*)p;
  int i;
  for (i = 0; i < pIp -> cl->nupvalues; i++)  /* mark its upvalues */
    markvalue(pIp -> g, pIp -> &cl->upvalue[i]);
  *(pIp -> ret) = 1 + cl->nupvalues;
}