#include "markmt.h"
void markmtFun(void *p) 
{
    markmt *pIp = (markmt*)p;
  int i;
  for (i=0; i < LUA_NUMTYPES; i++)
    markobjectN(pIp -> g, pIp -> g->mt[i]);
}