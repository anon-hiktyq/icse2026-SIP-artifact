
#include "findlast.h"

/*@
  requires \valid(pIp);
  requires \valid(pIp->p);
  assigns pIp->p, pIp->ret;
  ensures \valid(pIp->ret);
  ensures *(pIp->ret) == NULL;
*/
void findlastFun(findlast *pIp) 
{
  /*@
    loop invariant \valid(pIp);
    loop invariant \valid(pIp->p);
    loop invariant \valid(*pIp->p);
    loop assigns pIp->p;
    loop variant (*(pIp->p) != NULL) ? 1 : 0;
  */
  while (*(pIp->p) != NULL)
    pIp->p = &(*(pIp->p))->next;
  pIp->ret = pIp->p;
}
