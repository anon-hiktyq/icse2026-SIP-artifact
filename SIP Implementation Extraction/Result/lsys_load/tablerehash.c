#include "tablerehash.h"
void tablerehashFun(void *p) 
{
    tablerehash *pIp = (tablerehash*)p;
  int i;
  for (i = (pIp->osize); i < (pIp->nsize); i++)  /* clear new elements */
    (pIp->vect)[i] = NULL;
  for (i = 0; i < (pIp->osize); i++) {  /* rehash old part of the array */
    TString *p = (pIp->vect)[i];
    (pIp->vect)[i] = NULL;
    while (p) {  /* for each string in the list */
      TString *hnext = p->u.hnext;  /* save next */
      unsigned int h;{h = lmod(p->hash, pIp->nsize);}  /* new position */
      p->u.hnext = (pIp->vect)[h];  /* chain it into array */
      (pIp->vect)[h] = p;
      p = hnext;
    }
  }
}