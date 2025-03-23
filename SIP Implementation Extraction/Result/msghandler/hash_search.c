#include "hash_search.h"
void hash_searchFun(void *p) 
{
    hash_search *pIp = (hash_search*)p;
  lua_Unsigned i;
  if ((pIp->j) == 0) (pIp->j)++;  /* the caller ensures 'j + 1' is present */
  do {
    i = (pIp->j);  /* 'i' is a present index */
    {if (pIp->j <= l_castS2U(LUA_MAXINTEGER) / 2)
      (pIp->j) *= 2;
    else {
      (pIp->j) = LUA_MAXINTEGER;
      {int hashkeyisempty_ret_0;IPCALL(hashkeyisempty,iphashkeyisempty_0,.t = pIp->t,.key = pIp->j,.ret = &hashkeyisempty_ret_0);if (hashkeyisempty_ret_0)  /* t[j] not present? */
        break;  /* 'j' now is an absent index */
      else  /* weird case */
        *(pIp->ret) =  (pIp->j); } /* well, max integer is a boundary... */
    }}
  } while (!hashkeyisempty((pIp->t), (pIp->j)));  /* repeat until an absent t[j] */
  /* i < j  &&  t[i] present  &&  t[j] absent */
  while ((pIp->j) - i > 1u) {  /* do a binary search between them */
    lua_Unsigned m = (i + (pIp->j)) / 2;
    {int hashkeyisempty_ret_2;IPCALL(hashkeyisempty,iphashkeyisempty_2,.t = pIp->t,.key = m,.ret = &hashkeyisempty_ret_2);if (hashkeyisempty_ret_2) (pIp->j) = m;
    else i = m;}
  }
  *(pIp->ret) =  i;
}