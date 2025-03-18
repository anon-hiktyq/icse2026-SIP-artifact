
#include "luaO_ceillog2.h"

/*@ axiomatic CeilLog2 {
      logic integer ceil_log2(integer x) = 
        x <= 1 ? 0 : 1 + ceil_log2(x / 2);
    }
*/

/*@
  requires \valid(pIp);
  requires \valid(pIp->ret);
  requires pIp->x > 0;
  assigns pIp->x, *(pIp->ret);
  ensures *(pIp->ret) == ceil_log2(\old(pIp->x));
*/
void luaO_ceillog2Fun(luaO_ceillog2 *pIp) 
{
  static const lu_byte log_2[256] = {  /* log_2[i - 1] = ceil(log2(i)) */
    0,1,2,2,3,3,3,3,4,4,4,4,4,4,4,4,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,
    6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,
    7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,
    7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,
    8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,
    8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,
    8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,
    8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8
  };
  int l = 0;
  pIp -> x--;
  /*@ loop invariant 0 <= l;
      loop invariant pIp->x == (\at(pIp->x, Pre) >> l);
      loop invariant l % 8 == 0;
      loop assigns l, pIp->x;
      loop variant 256 - pIp->x;
  */
  while (pIp -> x >= 256) { 
    l += 8; 
    pIp -> x >>= 8; 
  }
  *(pIp -> ret) = cast_byte(l + log_2[pIp->x]);
}
