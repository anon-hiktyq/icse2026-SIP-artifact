
#include "luaO_utf8esc.h"

/*@ axiomatic UTF8Encoding {
      logic integer utf8_length(integer x) =
        x < 128 ? 1 :
        x < 2048 ? 2 :
        x < 65536 ? 3 :
        x < 2097152 ? 4 :
        x < 67108864 ? 5 : 6;

      // Define UTF8BUFFSZ as a logic constant
      logic integer UTF8BUFFSZ = 6;
    }
*/

/*@
  requires \valid(pIp);
  requires \valid(pIp->buff + (0..UTF8BUFFSZ-1));
  requires \valid(pIp->ret);
  requires pIp->x <= 2147483647; // 0x7FFFFFFFu in decimal
  assigns pIp->n, pIp->buff[0..UTF8BUFFSZ-1], *(pIp->ret);
  ensures pIp->n == utf8_length(\old(pIp->x));
  ensures *(pIp->ret) == pIp->n;
*/
void luaO_utf8escFun(luaO_utf8esc *pIp) 
{
  pIp -> n = 1;  /* number of bytes put in buffer (backwards) */
  lua_assert(pIp -> x <= 2147483647); // 0x7FFFFFFFu in decimal
  if (pIp -> x < 128)  /* ascii? */
    pIp -> buff[UTF8BUFFSZ - 1] = cast_char(pIp -> x);
  else {  /* need continuation bytes */
    unsigned int mfb = 63;  /* maximum that fits in first byte */
    /*@
      loop invariant 1 <= pIp->n <= 6;
      loop invariant mfb == 63 >> (pIp->n - 1); // 0x3f in decimal
      loop invariant \forall integer i; 0 <= i < pIp->n - 1 ==> 
        (pIp->buff[UTF8BUFFSZ - (pIp->n - i)] & 192) == 128; // 0xC0 and 0x80 in decimal
      loop assigns pIp->n, pIp->buff[UTF8BUFFSZ - pIp->n .. UTF8BUFFSZ - 1];
      loop variant pIp->x; // Ensure the variant is strictly decreasing
    */
    do {  /* add continuation bytes */
      pIp -> buff[UTF8BUFFSZ - (pIp -> n++)] = cast_char(128 | (pIp -> x & 63)); // 0x80 and 0x3f in decimal
      pIp -> x >>= 6;  /* remove added bits */
      mfb >>= 1;  /* now there is one less bit available in first byte */
    } while (pIp -> x > mfb);  /* still needs continuation byte? */
    pIp -> buff[UTF8BUFFSZ - pIp -> n] = cast_char((~mfb << 1) | pIp -> x);  /* add first byte */
  }
  *(pIp -> ret) = pIp->n;
}
