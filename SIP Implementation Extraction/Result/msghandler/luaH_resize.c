#include "luaH_resize.h"
void luaH_resizeFun(void *p) 
{
    luaH_resize *pIp = (luaH_resize*)p;
  Table newt;  /* to keep the new hash part */
  unsigned oldasize = (pIp->t)->asize;
  Value *newarray;
  if ((pIp->newasize) > MAXASIZE)
    {IPCALL(luaG_runerror,ipluaG_runerror_0);}
  /* create new hash part with appropriate size into 'newt' */
  newt.flags = 0;
  {IPCALL(setnodevector,ipsetnodevector_0,.L = pIp->L,.t = &newt,.size = pIp->nhsize);}
  if ((pIp->newasize) < oldasize) {  /* will array shrink? */
    /* re-insert into the new hash the elements from vanishing slice */
    {IPCALL(exchangehashpart,ipexchangehashpart_1,.t1 = pIp->t,.t2 = &newt);}  /* pretend table has new hash */
    {IPCALL(reinsertOldSlice,ipreinsertOldSlice_0,.t = pIp->t,.oldasize = oldasize,.newasize = pIp->newasize);}
    {IPCALL(exchangehashpart,ipexchangehashpart_0,.t1 = pIp->t,.t2 = &newt);}  /* restore old hash (in case of errors) */
  }
  /* allocate new array */
  {Value * resizearray_ret_0;IPCALL(resizearray,ipresizearray_0,.L = pIp->L,.t = pIp->t,.oldasize = oldasize,.newasize = pIp->newasize,.ret = resizearray_ret_0);newarray = resizearray_ret_0;}
  {if (l_unlikely(newarray == NULL && pIp->newasize > 0)) {  /* allocation failed? */
    {IPCALL(freehash,ipfreehash_0,.L = pIp->L,.t = &newt);}  /* release new hash part */
    {luaM_error(pIp->L);}  /* raise error (with array unchanged) */
  }}
  /* allocation ok; initialize new part of the array */
  {IPCALL(exchangehashpart,ipexchangehashpart_2,.t1 = pIp->t,.t2 = &newt);}  /* 't' has the new hash ('newt' has the old) */
  (pIp->t)->array = newarray;  /* set new array part */
  (pIp->t)->asize = (pIp->newasize);
  if (newarray != NULL)
    {*lenhint(pIp->t) = pIp->newasize / 2u;}  /* set an initial hint */
  {IPCALL(clearNewSlice,ipclearNewSlice_0,.t = pIp->t,.oldasize = oldasize,.newasize = pIp->newasize);}
  /* re-insert elements from old hash part into new parts */
  {IPCALL(reinserthash,ipreinserthash_0,.L = pIp->L,.ot = &newt,.t = pIp->t);}  /* 'newt' now has the old hash */
  {IPCALL(freehash,ipfreehash_1,.L = pIp->L,.t = &newt);}  /* free old hash part */
}