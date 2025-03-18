#include "initbuff.h"
void initbuffFun(void *p) 
{
    initbuff *pIp = (initbuff*)p;
  pIp -> buff->pIp -> L = pIp -> L;
  pIp -> buff->b = pIp -> buff->space;
  pIp -> buff->buffsize = sizeof(pIp -> buff->space);
  pIp -> buff->blen = 0;
  pIp -> buff->err = 0;
}