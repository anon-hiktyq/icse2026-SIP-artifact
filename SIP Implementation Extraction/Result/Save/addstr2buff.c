#include "addstr2buff.h"
void addstr2buffFun(void *p) 
{
    addstr2buff *pIp = (addstr2buff*)p;
  size_t left = (pIp->buff)->buffsize - (pIp->buff)->blen;  /* space left in the buffer */
  if ((pIp->buff)->err)  /* do nothing else after an error */
    return;
  if ((pIp->slen) > left) {  /* new string doesn't fit into current buffer? */
    if ((pIp->slen) > ((MAX_SIZE/2) - (pIp->buff)->blen)) {  /* overflow? */
      memcpy((pIp->buff)->b + (pIp->buff)->blen, (pIp->str), left);  /* copy what it can */
      (pIp->buff)->blen = (pIp->buff)->buffsize;
      (pIp->buff)->err = 2;  /* doesn't add anything else */
      return;
    }
    else {
      size_t newsize = (pIp->buff)->buffsize + (pIp->slen);  /* limited to MAX_SIZE/2 */
      char newb;{newb = (pIp->buff->b == pIp->buff->space)  /* still using static space? */
        ? luaM_reallocvector(pIp->buff->L, NULL, 0, newsize, char)
        : luaM_reallocvector(pIp->buff->L, pIp->buff->b, pIp->buff->buffsize, newsize,
                                                               char);}
      if (newb == NULL) {  /* allocation error? */
        (pIp->buff)->err = 1;  /* signal a memory error */
        return;
      }
      if ((pIp->buff)->b == (pIp->buff)->space)  /* new buffer (not reallocated)? */
        memcpy(newb, (pIp->buff)->b, (pIp->buff)->blen);  /* copy previous content */
      (pIp->buff)->b = newb;  /* set new (larger) buffer... */
      (pIp->buff)->buffsize = newsize;  /* ...and its new size */
    }
  }
  memcpy((pIp->buff)->b + (pIp->buff)->blen, (pIp->str), (pIp->slen));  /* copy new content */
  (pIp->buff)->blen += (pIp->slen);
}