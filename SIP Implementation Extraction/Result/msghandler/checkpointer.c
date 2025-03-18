#include "checkpointer.h"
void checkpointerFun(void *p) 
{
    checkpointer *pIp = (checkpointer*)p;
  if (pIp -> o == pIp -> *p)
    pIp -> *p = pIp -> o->next;
}