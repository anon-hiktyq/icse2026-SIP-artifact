#include "binsearch.h"
void binsearchFun(void *p) 
{
    binsearch *pIp = (binsearch*)p;
  {lua_assert(pIp->i <= pIp->j);}
  while ((pIp->j) - (pIp->i) > 1u) {  /* binary search */
    unsigned int m = ((pIp->i) + (pIp->j)) / 2;
    {int arraykeyisempty_ret_0;IPCALL(arraykeyisempty,iparraykeyisempty_0,.t = pIp->array,.key = m,.ret = &arraykeyisempty_ret_0);if (arraykeyisempty_ret_0) (pIp->j) = m;
    else (pIp->i) = m;}
  }
  *(pIp->ret) =  (pIp->i);
}