
#include "luaO_utf8esc.h"

/*@
  requires \valid(pIp);
  requires \valid(pIp->buff + (0..99));
  requires \valid(pIp->ret);
  requires pIp->x <= 0x7FFFFFFFu;
  assigns pIp->n, pIp->buff[0..99], *(pIp->ret);
  ensures *(pIp->ret) == pIp->n;
  ensures 1 <= pIp->n && pIp->n <= 100;
*/
void luaO_utf8escFun(luaO_utf8esc *pIp) 
{
  pIp -> n = 1;  /* number of bytes put in buffer (backwards) */
  lua_assert(pIp -> x <= 0x7FFFFFFFu);
  if (pIp -> x < 0x80)  /* ascii? */
    pIp -> buff[99] = cast_char(pIp -> x);
  else {  /* need continuation bytes */
    unsigned int mfb = 0x3f;  /* maximum that fits in first byte */
    /*@
      loop invariant 1 <= pIp->n && pIp->n <= 100;
      loop invariant mfb == 0x3f >> (pIp->n - 1);
      loop invariant pIp->x <= 0x7FFFFFFFu;
      loop assigns pIp->n, pIp->buff[100 - pIp->n .. 99], pIp->x, mfb;
      loop variant pIp->x;
    */
    do {  /* add continuation bytes */
      pIp -> buff[100 - (pIp -> n++)] = cast_char(0x80 | (pIp -> x & 0x3f));
      pIp -> x >>= 6;  /* remove added bits */
      mfb >>= 1;  /* now there is one less bit available in first byte */
    } while (pIp -> x > mfb);  /* still needs continuation byte? */
    pIp -> buff[100 - pIp -> n] = cast_char((~mfb << 1) | pIp -> x);  /* add first byte */
  }
  *(pIp -> ret) = pIp->n;
}
