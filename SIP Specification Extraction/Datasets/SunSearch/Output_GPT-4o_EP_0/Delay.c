
#include "Delay.h"

/*@ 
  requires \valid(pIp);
  requires \valid(pIp + (0..sizeof(Delay)-1));
  requires pIp->delaytime >= 0;
  assigns \nothing;
*/
void DelayFun(Delay *pIp)
{
    unint16 uidt;

    /*@ 
      loop invariant 0 <= uidt <= pIp->delaytime;
      loop assigns uidt;
      loop variant pIp->delaytime - uidt;
    */
    for (uidt = 0; uidt < pIp->delaytime; uidt++)
    {
       ;
    }

    return;
}
