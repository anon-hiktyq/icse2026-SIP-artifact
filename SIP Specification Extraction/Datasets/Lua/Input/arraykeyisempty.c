#include "arraykeyisempty.h"

void arraykeyisemptyFun(arraykeyisempty *pIp) 
{

  int tag = * getArrTag(pIp -> t, pIp -> key - 1);

  *(pIp -> ret) = tagisempty(tag);
}