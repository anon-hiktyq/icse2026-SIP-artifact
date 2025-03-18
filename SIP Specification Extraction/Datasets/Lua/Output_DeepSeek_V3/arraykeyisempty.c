
#include "arraykeyisempty.h"

/*@
  requires \valid(pIp) && \valid(pIp->t + (0..pIp->key-1));
  requires \valid(pIp->ret);
  assigns *(pIp->ret);
  ensures *(pIp->ret) == \old(tagisempty(*getArrTag(pIp->t, pIp->key - 1)));
*/
void arraykeyisemptyFun(arraykeyisempty *pIp) 
{
  int tag = *getArrTag(pIp->t, pIp->key - 1);

  *(pIp->ret) = tagisempty(tag);
}
