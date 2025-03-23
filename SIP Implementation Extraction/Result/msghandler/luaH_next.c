#include "luaH_next.h"
void luaH_nextFun(void *p) 
{
    luaH_next *pIp = (luaH_next*)p;
  unsigned int asize = (pIp->t)->asize;
  unsigned int i;{i = findindex(pIp->L, pIp->t, s2v(pIp->key), asize);}  /* find original key */
  for (; i < asize; i++) {  /* try first array part */
    lu_byte tag;{tag = *getArrTag(pIp->t, i);}
    {if (!tagisempty(tag)) {  /* a non-empty entry? */
      {setivalue(s2v(pIp->key), cast_int(i) + 1);}
      {farr2val(pIp->t, i, tag, s2v(pIp->key + 1));}
      *(pIp->ret) =  1;
    }}
  }
  for (i -= asize; i < sizenode((pIp->t)); i++) {  /* hash part */
    {if (!isempty(gval(gnode(pIp->t, i)))) {  /* a non-empty entry? */
      Node n;{n = gnode(pIp->t, i);}
      {getnodekey(pIp->L, s2v(pIp->key), n);}
      {setobj2s(pIp->L, pIp->key + 1, gval(n));}
      *(pIp->ret) =  1;
    }}
  }
  *(pIp->ret) =  0;  /* no more elements */
}