#include "exchangehashpart.h"
void exchangehashpartFun(void *p) 
{
    exchangehashpart *pIp = (exchangehashpart*)p;
  lu_byte lsizenode = (pIp->t1)->lsizenode;
  Node *node = (pIp->t1)->node;
  int bitdummy1 = (pIp->t1)->flags & BITDUMMY;
  (pIp->t1)->lsizenode = (pIp->t2)->lsizenode;
  (pIp->t1)->node = (pIp->t2)->node;
  {pIp->t1->flags = cast_byte((pIp->t1->flags & NOTBITDUMMY) | (pIp->t2->flags & BITDUMMY));}
  (pIp->t2)->lsizenode = lsizenode;
  (pIp->t2)->node = node;
  {pIp->t2->flags = cast_byte((pIp->t2->flags & NOTBITDUMMY) | bitdummy1);}
}