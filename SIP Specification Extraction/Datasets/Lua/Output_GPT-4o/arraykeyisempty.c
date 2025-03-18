
#include "arraykeyisempty.h"

/*@ axiomatic TagFunctions {
      logic int tagisempty(int tag);
      logic int* getArrTag(int* arr, int index);
    }
*/

/*@
  requires \valid(pIp) && \valid(pIp->t) && \valid(pIp->ret);
  requires pIp->key > 0;

  ensures \valid(pIp->ret);
  ensures *(pIp->ret) == tagisempty(*getArrTag(pIp->t, pIp->key - 1));

  assigns *(pIp->ret);
*/
void arraykeyisemptyFun(arraykeyisempty *pIp) 
{
  /*@ assert \valid(pIp) && \valid(pIp->t) && \valid(pIp->ret); */
  /*@ assert pIp->key > 0; */
  
  int tag = *getArrTag(pIp->t, pIp->key - 1);

  *(pIp->ret) = tagisempty(tag);
}
