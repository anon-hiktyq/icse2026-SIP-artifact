#include "retpsetcode.h"
void retpsetcodeFun(void *p) 
{
    retpsetcode *pIp = (retpsetcode*)p;
  if (isabstkey(pIp -> slot))
    *(pIp -> ret) = HNOTFOUND; /* no pIp -> slot with that key */
  else  /* return node encoded */
    *(pIp -> ret) = cast_int((cast(Node*, slot) - t->node)) + HFIRSTNODE;
}