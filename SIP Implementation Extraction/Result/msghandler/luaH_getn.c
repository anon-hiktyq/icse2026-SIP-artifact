#include "luaH_getn.h"
void luaH_getnFun(void *p) 
{
    luaH_getn *pIp = (luaH_getn*)p;
  unsigned asize = pIp -> t->asize;
  if (asize > 0) {  /* is there an array part? */
    const unsigned maxvicinity = 4;
    unsigned limit = *lenhint(pIp -> t);  /* start with the hint */
    if (limit == 0)
      limit = 1;  /* make limit a valid index in the array */
    {int arraykeyisempty_ret_4;IPCALL(arraykeyisempty,iparraykeyisempty_1,.t = pIp->t,.key = limit,.ret = pIp->&arraykeyisempty_ret_4);if ((arraykeyisempty_ret_4) {  /* pIp -> t[limit] empty? */
      /* there must be a border before 'limit' */
      unsigned i;
      /* look for a border in the vicinity of the hint */
      for (i = 0; i < maxvicinity && limit > 1; i++) {
        limit--;
        {int arraykeyisempty_ret_3;IPCALL(arraykeyisempty,iparraykeyisempty_0,.t = pIp->t,.key = limit,.ret = pIp->&arraykeyisempty_ret_3);if (!(arraykeyisempty_ret_3)
          *(pIp -{lua_Unsigned new}int_ret_2;IPCALL(newhint,ipnewhint_0,.t = pIp->t,.hint = limit,.ret = pIp->&newhint_ret_2);}, limit); /* 'limit' is a border */
      }
      /* t[limit] still empty; search for a border in [0, limit) */
      *(pIp -> ret) = newhint(t, binsearch(t, 0, limit));
    }
    else {  /* 'limit' is present in table; look for a border after it */
      unsigned i;
      /* look for a border in the vicinity of the hint */
      for (i = 0; i < maxvicinity && limit < asize; i++) {
        limit++;
        if (arraykeyisempty(pIp -> t, limit))
          *(pIp -> ret) = newhint(t, limit - 1); /* 'limit - 1' is a border */
      }
      if (arraykeyisempty(pIp -> t, asize)) {  /* last element empty? */
        /* t[limit] not empty; search for a border in [limit, asize) */
        *(pIp -> ret) = newhint(t, binsearch(t, limit, asize));
      }
    }}
    /* last element non empty; set a hint to speed up finding that again */
    /* (keys in the hash part cannot be hints) */
    *lenhint(pIp -> t) = asize;
  }
  /* no array part or t[asize] is not empty; check the hash part */
  lua_assert(asize == 0 || !arraykeyisempty(pIp -> t, asize));
  {int hashkeyisempty_ret_1;IPCALL(hashkeyisempty,iphashkeyisempty_0,.t = pIp->t,.key = asize + 1,.ret = pIp->&hashkeyisempty_ret_1);if (isdummy(pIp -> t) || (hashkeyisempty_ret_1)
    *(pIp -> ret) = asize; /* 'asize + 1' is empty */
  else  /* 'asize + 1' is also non empty */
    *(pIp -{lua_Unsigned hash_se}rch_ret_0;IPCALL(hash_search,iphash_search_0,.t = pIp->t,.j = asize,.ret = pIp->&hash_search_ret_0);}, asize);
}