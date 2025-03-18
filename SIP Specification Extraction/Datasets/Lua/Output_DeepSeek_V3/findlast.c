
#include "findlast.h"

/* Assuming struct node is defined in findlast.h as follows:
   struct node {
       struct node* next;
   };
*/

/*@ axiomatic LinkedList {
      predicate valid_list(struct node* p) = 
        p == \null || (\valid(p) && \valid(p->next) && valid_list(p->next));
    }
*/

/*@
  requires \valid(pIp);
  requires \valid(pIp->p);
  requires valid_list(*(pIp->p));
  assigns pIp->p, pIp->ret;
  ensures pIp->ret == \null || (\valid(pIp->ret) && *(pIp->ret) == \null);
*/
void findlastFun(findlast *pIp) 
{
  /*@
    loop invariant valid_list(*(pIp->p));
    loop assigns pIp->p;
    loop variant *(pIp->p) != \null ? 1 : 0;
  */
  while (*(pIp->p) != NULL) {
    pIp->p = &(*(pIp->p))->next;
  }
  pIp->ret = pIp->p;
}
