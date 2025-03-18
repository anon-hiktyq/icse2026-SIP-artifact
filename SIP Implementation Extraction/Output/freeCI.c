#include "freeCI.h"
void freeCIFun(void *p) 
{
    freeCI *pIp = (freeCI*)p;
  CallInfo *ci = pIp -> L->ci;
  CallInfo *next = ci->next;
  ci->next = NULL;
  while ((ci = next) != NULL) {
    next = ci->next;
    luaM_free(pIp -> L, ci);
    pIp -> L->nci--;
  }
}