
#include "luaV_shiftl.h"

/*@ axiomatic BitwiseShift {
      logic integer shift_left(integer x, integer y);
      logic integer shift_right(integer x, integer y);

      axiom shift_left_def:
        \forall integer x, y; y >= 0 ==> shift_left(x, y) == x << y;

      axiom shift_right_def:
        \forall integer x, y; y >= 0 ==> shift_right(x, y) == x >> y;
    }
*/

/*@ requires \valid(pIp);
    ensures pIp->y <= -NBITS || pIp->y >= NBITS ==> pIp->x == \old(pIp->x);
    ensures pIp->y > -NBITS && pIp->y < NBITS ==> 
            (pIp->y < 0 ==> pIp->x == shift_right(\old(pIp->x), -pIp->y)) &&
            (pIp->y >= 0 ==> pIp->x == shift_left(\old(pIp->x), pIp->y));
    assigns pIp->x;
*/
void luaV_shiftlFun(luaV_shiftl *pIp) 
{
  if (pIp->y < 0) {  /* shift right? */
    if (pIp->y <= -NBITS) return;
    else pIp->x = intop(>>, pIp->x, -pIp->y);
  }
  else {  /* shift left */
    if (pIp->y >= NBITS) return;
    else pIp->x = intop(<<, pIp->x, pIp->y);
  }
}
