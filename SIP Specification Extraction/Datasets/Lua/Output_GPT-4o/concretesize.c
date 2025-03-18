
#include "concretesize.h"

/*@
  requires \valid(pIp);
  requires \valid(pIp->ret);
  assigns *(pIp->ret);
  ensures *(pIp->ret) == 0 <==> pIp->size == 0;
  ensures *(pIp->ret) == pIp->size * (sizeof(Value) + 1) + sizeof(unsigned) <==> pIp->size != 0;
*/
void concretesizeFun(concretesize *pIp) 
{
  /*@ assert \valid(pIp); */
  /*@ assert \valid(pIp->ret); */
  
  if (pIp->size == 0) {
    *(pIp->ret) = 0;
    /*@ assert *(pIp->ret) == 0; */
  } else {
    /* space for the two arrays plus an unsigned in between */
    *(pIp->ret) = pIp->size * (sizeof(Value) + 1) + sizeof(unsigned);
    /*@ assert *(pIp->ret) == pIp->size * (sizeof(Value) + 1) + sizeof(unsigned); */
  }
}
