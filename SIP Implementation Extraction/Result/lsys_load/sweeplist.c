#include "sweeplist.h"
void sweeplistFun(void *p) 
{
    sweeplist *pIp = (sweeplist*)p;
  global_State g;{g = G(pIp->L);}
  int ow;{ow = otherwhite(g);}
  int white;{white = luaC_white(g);}  /* current white */
  while (*(pIp->p) != NULL && (pIp->countin)-- > 0) {
    GCObject *curr = *(pIp->p);
    int marked = curr->marked;
    {if (isdeadm(ow, marked)) {  /* is 'curr' dead? */
      *(pIp->p) = curr->next;  /* remove 'curr' from list */
      {IPCALL(freeobj,ipfreeobj_0,.L = pIp->L,.o = curr);}  /* erase 'curr' */
    }
    else {  /* change mark to 'white' and age to 'new' */
      {curr->marked = cast_byte((marked & ~maskgcbits) | white | G_NEW);}
      (pIp->p) = &curr->next;  /* go to next element */
    }}
  }
  pIp->ret =  (*(pIp->p) == NULL) ? NULL : (pIp->p);
}