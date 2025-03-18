
#include "luaO_applyparam.h"

/*@
  requires \valid(pIp);
  requires \valid(pIp->ret);
  requires pIp->p >= 0;
  requires pIp->x >= 0;
  assigns *(pIp->ret);
  ensures *(pIp->ret) >= 0 && *(pIp->ret) <= 100;
  behavior positive_exponent:
    assumes (pIp->p >> 4) > 0;
    ensures *(pIp->ret) == 100 || *(pIp->ret) == (\old(pIp->x) * (\old(pIp->p) & 0xF)) << (\old(pIp->p >> 4) - 8);
  behavior negative_exponent:
    assumes (pIp->p >> 4) <= 0;
    ensures *(pIp->ret) == 100 || *(pIp->ret) == (\old(pIp->x) * (\old(pIp->p) & 0xF)) >> (8 - \old(pIp->p >> 4));
  complete behaviors;
  disjoint behaviors;
*/
void luaO_applyparamFun(luaO_applyparam *pIp) 
{
  unsigned int m = pIp -> p & 0xF;  /* mantissa */
  int e = (pIp -> p >> 4);  /* exponent */
  if (e > 0) {  /* normalized? */
    e--;  /* correct exponent */
    m += 0x10;  /* correct mantissa; maximum value is 0x1F */
  }
  e -= 7;  /* correct excess-7 */
  if (e >= 0) {
    if (pIp -> x < ( 100 / 0x1F) >> e)  /* no overflow? */
      *(pIp -> ret) = (pIp->x * m) << e; /* order doesn't matter here */
    else  /* real overflow */
      *(pIp -> ret) = 100;
  }
  else {  /* negative exponent */
    e = -e;
    if (pIp -> x < 100 / 0x1F)  /* multiplication cannot overflow? */
      *(pIp -> ret) = (pIp->x * m) >> e; /* multiplying first gives more precision */
    else if ((pIp -> x >> e) <  100 / 0x1F)  /* cannot overflow after shift? */
      *(pIp -> ret) = (pIp->x >> e) * m;
    else  /* real overflow */
      *(pIp -> ret) = 100;
  }
}
