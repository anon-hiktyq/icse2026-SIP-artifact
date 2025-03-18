#include "luaO_codeparam.h"
void luaO_codeparamFun(void *p) 
{
    luaO_codeparam *pIp = (luaO_codeparam*)p;
  if (pIp -> p >= (cast(lu_mem, 0x1F) << (0xF - 7 - 1)) * 100u)  /* overflow? */
    *(pIp -> ret) = 0xFF; /* return maximum value */
  else {
    pIp -> p = (cast(l_uint32, pIp -> p) * 128 + 99) / 100;  /* round up the division */
    if (pIp -> p < 0x10) {  /* subnormal number? */
      /* exponent bits are already zero; nothing else to do */
      *(pIp -> ret) = cast_byte(p);
    }
    else {  /* pIp -> p >= 0x10 implies ceil(log2(pIp -> p + 1)) >= 5 */
      /* preserve 5 bits in 'p' */
      unsigned log = luaO_ceillog2(pIp -> p + 1) - 5u;
      *(pIp -> ret) = cast_byte(((p >> log) - 0x10) | ((log + 1) << 4));
    }
  }
}