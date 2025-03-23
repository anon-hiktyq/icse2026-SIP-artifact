#include "arraykeyisempty.h"
void arraykeyisemptyFun(void *p) 
{
    arraykeyisempty *pIp = (arraykeyisempty*)p;
  int tag;{tag = *getArrTag(pIp->t, pIp->key - 1);}
  *(pIp->ret) =  tagisempty(tag);
}