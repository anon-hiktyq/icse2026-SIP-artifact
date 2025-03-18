#include "hash_search.h"
void hash_searchFun(void *p) 
{
    hash_search *pIp = (hash_search*)p;
  lua_Unsigned i;
  if pIp -> (j == 0) j++;  /* the caller ensures 'pIp -> j + 1' is present */
  do {
    i = pIp -> j;  /* 'i' is a present index */
    if (pIp -> j <= l_castS2U(LUA_MAXINTEGER) / 2)
      pIp -> j *= 2;
    else {
      pIp -> j = LUA_MAXINTEGER;
      {int hashkeyisempty_ret_1;IPCALL(hashkeyisempty,iphashkeyisempty_1,.t = pIp->t,.key = j,.ret = pIp->&hashkeyisempty_ret_1);if ((hashkeyisempty_ret_1)  /* pIp -> t[pIp -> j] not present? */
        break;  /* 'pIp -> j' now is an absent index */
      else  /* weird case */
        *(pIp ->}ret) = j; /* well, max integer is a boundary... */
    }
  } while (!hashkeyisempty(pIp -> t, pIp -> j));  /* repeat until an absent pIp -> t[pIp -> j] */
  /* i < j  &&  t[i] present  &&  t[j] absent */
  while (pIp -> j - i > 1u) {  /* do a binary search between them */
    lua_Unsigned m = (i + pIp -> j) / 2;
    {int hashkeyisempty_ret_0;IPCALL(hashkeyisempty,iphashkeyisempty_0,.t = pIp->t,.key = m,.ret = pIp->&hashkeyisempty_ret_0);if ((hashkeyisempty_ret_0) pIp -> j = m;
    else i = m}
  }
  *(pIp -> ret) = i;
}