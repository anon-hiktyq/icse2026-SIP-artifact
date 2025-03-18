
#include "luaO_applyparam.h"

/*@ axiomatic OverflowChecks {
      logic integer safe_shift(integer x, integer e) = 
        e >= 0 ? x << e : x >> (-e);
      logic integer safe_mult(integer x, integer m, integer e) = 
        e >= 0 ? (x * m) << e : (x * m) >> (-e);
    }
*/

/*@
  requires \valid(pIp);
  requires \valid(pIp->ret);
  requires pIp->x >= 0;
  assigns *(pIp->ret);
  ensures *(pIp->ret) == 100 || 
          (\exists integer m, e; 
           m == (pIp->p & 0xF) && 
           e == ((pIp->p >> 4) - 7) && 
           (*(pIp->ret) == safe_shift(pIp->x * m, e) || 
            *(pIp->ret) == safe_mult(pIp->x, m, e)));
*/
void luaO_applyparamFun(luaO_applyparam *pIp) 
{
  unsigned int m = pIp -> p & 0xF;  /* mantissa */
  int e = (pIp -> p >> 4);  /* exponent */

  /*@ assert m >= 0 && m <= 0xF; */
  /*@ assert e >= -127 && e <= 127; */  // Adjusted range for e

  if (e > 0) {  /* normalized? */
    e--;  /* correct exponent */
    m += 0x10;  /* correct mantissa; maximum value is 0x1F */
    /*@ assert m >= 0x10 && m <= 0x1F; */
  }
  e -= 7;  /* correct excess-7 */
  /*@ assert e >= -134 && e <= 120; */  // Adjusted range for e

  if (e >= 0) {
    /*@ assert e >= 0 && e <= 120; */  // Adjusted range for e
    if (pIp -> x < ( 100 / 0x1F) >> e)  /* no overflow? */
      *(pIp -> ret) = (pIp->x * m) << e; /* order doesn't matter here */
    else  /* real overflow */
      *(pIp -> ret) = 100;
  }
  else {  /* negative exponent */
    e = -e;
    /*@ assert e >= 0 && e <= 134; */  // Adjusted range for e
    if (pIp -> x < 100 / 0x1F)  /* multiplication cannot overflow? */
      *(pIp -> ret) = (pIp->x * m) >> e; /* multiplying first gives more precision */
    else if ((pIp -> x >> e) <  100 / 0x1F)  /* cannot overflow after shift? */
      *(pIp -> ret) = (pIp->x >> e) * m;
    else  /* real overflow */
      *(pIp -> ret) = 100;
  }
}
