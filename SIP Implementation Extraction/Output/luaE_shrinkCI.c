#include "luaE_shrinkCI.h"
void luaE_shrinkCIFun(void *p) 
{
    luaE_shrinkCI *pIp = (luaE_shrinkCI*)p;
  CallInfo *ci = pIp -> L->ci->next;  /* first free CallInfo */
  CallInfo *next;
  if (ci == NULL)
    return;  /* no extra elements */
  while ((next = ci->next) != NULL) {  /* two extra elements? */
    CallInfo *next2 = next->next;  /* next's next */
    ci->next = next2;  /* remove next from the list */
    pIp -> L->nci--;
    luaM_free(pIp -> L, next);  /* free next */
    if (next2 == NULL)
      break;  /* no more elements */
    else {
      next2->previous = ci;
      ci = next2;  /* continue */
    }
  }
}