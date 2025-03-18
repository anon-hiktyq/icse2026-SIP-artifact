#include "rehash.h"
void rehashFun(void *p) 
{
    rehash *pIp = (rehash*)p;
  unsigned asize;  /* optimal size for array part */
  Counters ct;
  unsigned i;
  unsigned nsize;  /* size for the hash part */
  /* reset counts */
  for (i = 0; i <= MAXABITS; i++) ct.nums[i] = 0;
  ct.na = 0;
  ct.deleted = 0;
  ct.total = 1;  /* count extra key */
  if (ttisinteger(pIp -> ek))
    {IPCALL(countint,ipcountint_0,.key = ivalue(pIp->ek),.ct = &ct);}  /* extra key may go to array */
  {IPCALL(numusehash,ipnumusehash_0,.t = pIp->t,.ct = &ct);}  /* count keys in hash part */
  if (ct.na == 0) {
    /* no new keys to enter array part; keep it with the same size */
    asize = pIp -> t->asize;
  }
  else {  /* compute best size for array part */
    numusearray(pIp -> t, &ct);  /* count keys in array part */
    asize = computesizes(&ct);  /* compute new size for array part */
  }
  /* all keys not in the array part go to the hash part */
  nsize = ct.total - ct.na;
  if (ct.deleted) {  /* table has deleted entries? */
    /* insertion-deletion-insertion: give hash some extra size to
       avoid repeated resizings */
    nsize += nsize >> 2;
  }
  /* resize the table to new computed sizes */
  {IPCALL(luaH_resize,ipluaH_resize_0,.L = pIp->L,.t = pIp->t,.newasize = asize,.nhsize = nsize);}
}