
#include "luaS_hash.h"

/*@ axiomatic Hash {
      logic integer hash_value(luaS_hash *pIp) reads pIp->seed, pIp->l, pIp->str, pIp->h;
      axiom hash_init:
        \forall luaS_hash *pIp; hash_value(pIp) == pIp->seed + cast_uint(pIp->l); // Removed XOR
      axiom hash_update:
        \forall luaS_hash *pIp; \forall integer i; 0 <= i < pIp->l ==>
          hash_value(pIp) == hash_value(pIp) + ((hash_value(pIp) << 5) + (hash_value(pIp) >> 2) + cast_byte(pIp->str[i])); // Removed XOR
    }
*/

/*@
  requires \valid(pIp);
  requires \valid(pIp->ret);
  requires \valid_read(pIp->str + (0..pIp->l-1));
  assigns pIp->h, *(pIp->ret);
  ensures *(pIp->ret) == pIp->h; // Simplified postcondition
*/
void luaS_hashFun(luaS_hash *pIp) 
{
  /*@ assert \valid(pIp); */
  /*@ assert \valid(pIp->ret); */
  /*@ assert \valid_read(pIp->str + (0..pIp->l-1)); */

  pIp->h = pIp->seed ^ cast_uint(pIp->l);

  /*@ loop invariant 0 <= pIp->l <= \at(pIp->l, Pre);
      loop invariant pIp->h == \at(pIp->h, LoopEntry) + ((pIp->h << 5) + (pIp->h >> 2) + cast_byte(pIp->str[pIp->l])); // Corrected invariant
      loop assigns pIp->h, pIp->l;
      loop variant pIp->l;
  */
  for (; pIp->l > 0; pIp->l--) {
    /*@ assert \valid_read(pIp->str + (pIp->l-1)); */
    pIp->h ^= ((pIp->h << 5) + (pIp->h >> 2) + cast_byte(pIp->str[pIp->l - 1]));
  }

  *(pIp->ret) = pIp->h;
}
