#include "luaH_getn.h"
void luaH_getnFun(void *p) 
{
    luaH_getn *pIp = (luaH_getn*)p;
  unsigned asize = (pIp->t)->asize;
  if (asize > 0) {  /* is there an array part? */
    const unsigned maxvicinity = 4;
    unsigned limit;{limit = *lenhint(pIp->t);}  /* start with the hint */
    if (limit == 0)
      limit = 1;  /* make limit a valid index in the array */
    {int arraykeyisempty_ret_0;IPCALL(arraykeyisempty,iparraykeyisempty_0,.t = pIp->t,.key = limit,.ret = &arraykeyisempty_ret_0);if (arraykeyisempty_ret_0) {  /* t[limit] empty? */
      /* there must be a border before 'limit' */
      unsigned i;
      /* look for a border in the vicinity of the hint */
      for (i = 0; i < maxvicinity && limit > 1; i++) {
        limit--;
        {int arraykeyisempty_ret_1;IPCALL(arraykeyisempty,iparraykeyisempty_1,.t = pIp->t,.key = limit,.ret = &arraykeyisempty_ret_1);if (!arraykeyisempty_ret_1)
          lua_Unsigned newhint_ret_0;IPCALL(newhint,ipnewhint_0,.t = pIp->t,.hint = limit,.ret = &newhint_ret_0);*(pIp->ret) =  newhint_ret_0; } /* 'limit' is a border */
      }
      /* t[limit] still empty; search for a border in [0, limit) */
      unsigned int binsearch_ret_0;IPCALL(binsearch,ipbinsearch_0,.array = pIp->t,.i = 0,.j = limit,.ret = &binsearch_ret_0);lua_Unsigned newhint_ret_1;IPCALL(newhint,ipnewhint_1,.t = pIp->t,.hint = binsearch_ret_0,.ret = &newhint_ret_1);*(pIp->ret) =  newhint_ret_1;
    }
    else {  /* 'limit' is present in table; look for a border after it */
      unsigned i;
      /* look for a border in the vicinity of the hint */
      for (i = 0; i < maxvicinity && limit < asize; i++) {
        limit++;
        {int arraykeyisempty_ret_2;IPCALL(arraykeyisempty,iparraykeyisempty_2,.t = pIp->t,.key = limit,.ret = &arraykeyisempty_ret_2);if (arraykeyisempty_ret_2)
          lua_Unsigned newhint_ret_2;IPCALL(newhint,ipnewhint_2,.t = pIp->t,.hint = limit - 1,.ret = &newhint_ret_2);*(pIp->ret) =  newhint_ret_2; } /* 'limit - 1' is a border */
      }
      {int arraykeyisempty_ret_3;IPCALL(arraykeyisempty,iparraykeyisempty_3,.t = pIp->t,.key = asize,.ret = &arraykeyisempty_ret_3);if (arraykeyisempty_ret_3) {  /* last element empty? */
        /* t[limit] not empty; search for a border in [limit, asize) */
        unsigned int binsearch_ret_1;IPCALL(binsearch,ipbinsearch_1,.array = pIp->t,.i = limit,.j = asize,.ret = &binsearch_ret_1);lua_Unsigned newhint_ret_3;IPCALL(newhint,ipnewhint_3,.t = pIp->t,.hint = binsearch_ret_1,.ret = &newhint_ret_3);*(pIp->ret) =  newhint_ret_3;
      }}
    }}
    /* last element non empty; set a hint to speed up finding that again */
    /* (keys in the hash part cannot be hints) */
    {*lenhint(pIp->t) = asize;}
  }
  /* no array part or t[asize] is not empty; check the hash part */
  {int arraykeyisempty_ret_4;IPCALL(arraykeyisempty,iparraykeyisempty_4,.t = pIp->t,.key = asize,.ret = &arraykeyisempty_ret_4);lua_assert(asize == 0 || !arraykeyisempty(pIp->t, asize));}
  {int hashkeyisempty_ret_0;IPCALL(hashkeyisempty,iphashkeyisempty_0,.t = pIp->t,.key = asize + 1,.ret = &hashkeyisempty_ret_0);if (isdummy(pIp->t) || hashkeyisempty_ret_0)
    *(pIp->ret) =  asize;  /* 'asize + 1' is empty */
  else  /* 'asize + 1' is also non empty */
    lua_Unsigned hash_search_ret_0;IPCALL(hash_search,iphash_search_0,.t = pIp->t,.j = asize,.ret = &hash_search_ret_0);*(pIp->ret) =  hash_search_ret_0;}
}