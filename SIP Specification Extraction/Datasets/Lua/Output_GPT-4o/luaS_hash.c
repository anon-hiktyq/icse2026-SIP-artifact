
#include "luaS_hash.h"

/*@ axiomatic HashFunction {
      logic integer hash_value(luaS_hash *pIp) reads pIp->seed, pIp->l, pIp->str[0..pIp->l-1], pIp->h;
      axiom hash_init:
        \forall luaS_hash *pIp; hash_value(pIp) == pIp->seed + cast_uint(pIp->l);
      axiom hash_update:
        \forall luaS_hash *pIp; \forall integer i; 0 <= i < pIp->l ==>
          hash_value(pIp) == hash_value(pIp) + ((hash_value(pIp) * 32) + (hash_value(pIp) / 4) + cast_byte(pIp->str[i]));
    }
*/

/*@
  requires \valid(pIp);
  requires \valid(pIp->str + (0..pIp->l-1));
  requires \valid(pIp->ret);
  assigns pIp->h, *(pIp->ret), pIp->l;
  ensures *(pIp->ret) == hash_value(pIp);
*/
void luaS_hashFun(luaS_hash *pIp) 
{
  pIp->h = pIp->seed + cast_uint(pIp->l);
  /*@ loop invariant 0 <= pIp->l <= \at(pIp->l, Pre);
      loop invariant pIp->h == hash_value(pIp);
      loop assigns pIp->h, pIp->l;
      loop variant pIp->l;
  */
  for (; pIp->l > 0; pIp->l--)
    pIp->h += ((pIp->h * 32) + (pIp->h / 4) + cast_byte(pIp->str[pIp->l - 1]));
  *(pIp->ret) = pIp->h;
}
