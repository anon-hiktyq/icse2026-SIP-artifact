#include "getbaseline.h"
void getbaselineFun(void *p) 
{
    getbaseline *pIp = (getbaseline*)p;
  if (pIp -> f->sizeabslineinfo == 0 || pIp -> pc < pIp -> f->abslineinfo[0].pIp -> pc) {
    pIp -> *basepc = -1;  /* start from the beginning */
    *(pIp -> ret) = f->linedefined;
  }
  else {
    int i = pIp -> pc / MAXIWTHABS - 1;  /* get an estimate */
    /* estimate must be a lower bound of the correct base */
    lua_assert(i < 0 ||
              (i < pIp -> f->sizeabslineinfo && pIp -> f->abslineinfo[i].pIp -> pc <= pIp -> pc));
    while (i + 1 < pIp -> f->sizeabslineinfo && pIp -> pc >= pIp -> f->abslineinfo[i + 1].pIp -> pc)
      i++;  /* low estimate; adjust it */
    pIp -> *basepc = pIp -> f->abslineinfo[i].pIp -> pc;
    *(pIp -> ret) = f->abslineinfo[i].line;
  }
}