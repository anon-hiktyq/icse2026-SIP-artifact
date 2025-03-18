
#include "GyroChoose.h"

/*@ axiomatic Sum_array {
      logic integer sum(unint32* array, integer begin, integer end) reads array[begin .. (end-1)];
      axiom empty:
        \forall unint32* a, integer b, e; b >= e ==> sum(a,b,e) == 0;
      axiom range:
        \forall unint32* a, integer b, e; b < e ==> sum(a,b,e) == sum(a,b,e-1) + (a[e-1] == TRUE ? 1 : 0);
    }
*/

/*@
  requires \valid(pIp);
  requires \valid(pIp->pGyroData);
  requires \valid(pIp->pGyroData->stateFlag + (0..8));
  requires \valid(pIp->pGyroData->SignFlag + (0..8));
  assigns pIp->pGyroData->JoinTotal, pIp->pGyroData->gyroStatus0, pIp->pGyroData->SignFlag[0..8];
  ensures pIp->pGyroData->JoinTotal == \old(pIp->pGyroData->JoinTotal) + 
           sum(\old(pIp->pGyroData->stateFlag), 0, 9);
  ensures pIp->pGyroData->gyroStatus0 == \old(pIp->pGyroData->gyroStatus0) | 
           (\let mask = 0; 
            \forall int i; 0 <= i < 9 ==> 
              (\old(pIp->pGyroData->stateFlag[i]) == TRUE ? mask |= (1 << i) : mask == mask));
*/
void GyroChooseFun(GyroChoose *pIp)
{
    unint08 i;

    pIp->pGyroData->JoinTotal = 0;
    pIp->pGyroData->gyroStatus0 = 0;

    /*@
      loop invariant 0 <= i <= 9;
      loop invariant \forall int j; 0 <= j < i ==> 
        (pIp->pGyroData->stateFlag[j] == TRUE ==> 
         pIp->pGyroData->SignFlag[pIp->pGyroData->JoinTotal - 1] == j);
      loop invariant pIp->pGyroData->JoinTotal == 
        sum(pIp->pGyroData->stateFlag, 0, i);
      loop invariant pIp->pGyroData->gyroStatus0 == 
        (\let mask = 0; 
         \forall int j; 0 <= j < i ==> 
           (pIp->pGyroData->stateFlag[j] == TRUE ? mask |= (1 << j) : mask == mask));
      loop assigns pIp->pGyroData->JoinTotal, pIp->pGyroData->gyroStatus0, pIp->pGyroData->SignFlag[0..8];
      loop variant 9 - i;
    */
    for (i = 0; i < 9; i++)
    {
        if (pIp->pGyroData->stateFlag[i] == TRUE)
        {
            pIp->pGyroData->SignFlag[pIp->pGyroData->JoinTotal] = i;
            pIp->pGyroData->JoinTotal++;
            pIp->pGyroData->gyroStatus0 = pIp->pGyroData->gyroStatus0 | (1 << i);
        }
    }

    return;
}
