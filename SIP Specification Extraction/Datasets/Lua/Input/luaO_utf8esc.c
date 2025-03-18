#include "luaO_utf8esc.h"
void luaO_utf8escFun(luaO_utf8esc *pIp) 
{
  pIp -> n = 1;  /* number of bytes put in buffer (backwards) */
  lua_assert(pIp -> x <= 0x7FFFFFFFu);
  if (pIp -> x < 0x80)  /* ascii? */
    pIp -> buff[UTF8BUFFSZ - 1] = cast_char(pIp -> x);
  else {  /* need continuation bytes */
    unsigned int mfb = 0x3f;  /* maximum that fits in first byte */
    do {  /* add continuation bytes */
      pIp -> buff[UTF8BUFFSZ - (pIp -> n++)] = cast_char(0x80 | (pIp -> x & 0x3f));
      pIp -> x >>= 6;  /* remove added bits */
      mfb >>= 1;  /* now there is one less bit available in first byte */
    } while (pIp -> x > mfb);  /* still needs continuation byte? */
    pIp -> buff[UTF8BUFFSZ - pIp -> n] = cast_char((~mfb << 1) | pIp -> x);  /* add first byte */
  }
  *(pIp -> ret) = pIp->n;
}