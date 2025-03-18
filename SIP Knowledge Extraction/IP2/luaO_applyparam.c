#include "luaO_applyparam.h"
void luaO_applyparamFun(void *p) 
{
    luaO_applyparam *pIp = (luaO_applyparam*)p;
  unsigned int m = pIp -> p & 0xF;  /* mantissa */
  int e = (pIp -> p >> 4);  /* exponent */
  if (e > 0) {  /* normalized? */
    e--;  /* correct exponent */
    m += 0x10;  /* correct mantissa; maximum value is 0x1F */
  }
  e -= 7;  /* correct excess-7 */
  if (e >= 0) {
    if (pIp -> x < (MAX_LMEM / 0x1F) >> e)  /* no overflow? */
      *(pIp -> ret) = (x * m) << e; /* order doesn't matter here */
    else  /* real overflow */
      *(pIp -> ret) = MAX_LMEM;
  }
  else {  /* negative exponent */
    e = -e;
    if (pIp -> x < MAX_LMEM / 0x1F)  /* multiplication cannot overflow? */
      *(pIp -> ret) = (x * m) >> e; /* multiplying first gives more precision */
    else if ((pIp -> x >> e) <  MAX_LMEM / 0x1F)  /* cannot overflow after shift? */
      *(pIp -> ret) = (x >> e) * m;
    else  /* real overflow */
      *(pIp -> ret) = MAX_LMEM;
  }
}