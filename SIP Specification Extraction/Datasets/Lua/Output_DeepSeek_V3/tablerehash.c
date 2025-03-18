
#include "tablerehash.h"

/*@ axiomatic HashTable {
      logic integer sum{T}(TString **arr, integer begin, integer end) reads arr[begin .. (end-1)];
      axiom empty:
        \forall TString **a, integer b, e; b >= e ==> sum(a,b,e) == 0;
      axiom range:
        \forall TString **a, integer b, e; b < e ==> sum(a,b,e) == sum(a,b,e-1) + (a[e-1] == NULL ? 0 : 1);
    }
*/

/*@
  requires \valid(pIp);
  requires \valid(pIp->vect + (0 .. pIp->nsize-1));
  requires pIp->osize <= pIp->nsize;
  assigns pIp->vect[0 .. pIp->nsize-1];
  ensures \forall integer i; 0 <= i < pIp->osize ==> pIp->vect[i] == NULL;
  ensures \forall integer i; pIp->osize <= i < pIp->nsize ==> pIp->vect[i] == NULL;
*/
void tablerehashFun(tablerehash *pIp) {
    int i;

    /*@
      loop invariant 0 <= i <= pIp->nsize;
      loop invariant \forall integer j; pIp->osize <= j < i ==> pIp->vect[j] == NULL;
      loop assigns i, pIp->vect[pIp->osize .. pIp->nsize-1];
      loop variant pIp->nsize - i;
    */
    for (i = pIp->osize; i < pIp->nsize; i++)  /* clear new elements */
        pIp->vect[i] = NULL;

    /*@
      loop invariant 0 <= i <= pIp->osize;
      loop invariant \forall integer j; 0 <= j < i ==> pIp->vect[j] == NULL;
      loop invariant \forall integer j; i <= j < pIp->osize ==> pIp->vect[j] == \at(pIp->vect[j], Pre);
      loop assigns i, pIp->vect[0 .. pIp->nsize-1];
      loop variant pIp->osize - i;
    */
    for (i = 0; i < pIp->osize; i++) {  /* rehash old part of the array */
        TString *p = pIp->vect[i];
        pIp->vect[i] = NULL;

        /*@
          loop invariant \valid(pIp->vect + (0 .. pIp->nsize-1));
          loop assigns p, pIp->vect[0 .. pIp->nsize-1];
          loop variant sum(pIp->vect, 0, pIp->nsize);
        */
        while (p) {  /* for each string in the list */
            TString *hnext = p->u.hnext;  /* save next */
            unsigned int h = lmod(p->hash, pIp->nsize);  /* new position */
            p->u.hnext = pIp->vect[h];  /* chain it into array */
            pIp->vect[h] = p;
            p = hnext;
        }
    }
}
