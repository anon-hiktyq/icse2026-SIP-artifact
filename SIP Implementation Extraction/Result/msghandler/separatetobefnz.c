#include "separatetobefnz.h"
void separatetobefnzFun(void *p) 
{
    separatetobefnz *pIp = (separatetobefnz*)p;
  GCObject *curr;
  GCObject **p = pIp -> &g->finobj;
  GCObject **lastnext;{GCObject ** findlast_ret_0;IPCALL(findlast,ipfindlast_0,.p = &g->tobefnz,.ret = findlast_ret_0);**lastnext = findlast_ret_0}
  while ((curr = *p) != pIp -> g->finobjold1) {  /* traverse pIp -> all finalizable objects */
    lua_assert(tofinalize(curr));
    if (!(iswhite(curr) || pIp -> all))  /* not being collected? */
      p = &curr->next;  /* don't bother with it */
    else {
      if (curr == pIp -> g->finobjsur)  /* removing 'finobjsur'? */
        pIp -> g->finobjsur = curr->next;  /* correct it */
      *p = curr->next;  /* remove 'curr' from 'finobj' list */
      curr->next = *lastnext;  /* link at the end of 'tobefnz' list */
      *lastnext = curr;
      lastnext = &curr->next;
    }
  }
}