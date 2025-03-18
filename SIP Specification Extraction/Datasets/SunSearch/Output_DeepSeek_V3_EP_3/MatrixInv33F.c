
#include "MatrixInv33F.h"

/*@ axiomatic MatrixInv33F {
      logic real determinant(MatrixInv33F *pIp) reads pIp->src[0..8], pIp->inv[0..8];
      axiom determinant_def:
        \forall MatrixInv33F *pIp; determinant(pIp) ==
          pIp->src[0] * (pIp->src[4] * pIp->src[8] - pIp->src[5] * pIp->src[7]) -
          pIp->src[1] * (pIp->src[3] * pIp->src[8] - pIp->src[5] * pIp->src[6]) +
          pIp->src[2] * (pIp->src[3] * pIp->src[7] - pIp->src[4] * pIp->src[6]);
    }
*/

/*@ requires \valid(pIp);
    requires \valid(pIp->ret);
    requires \valid_read(pIp->src + (0..8));
    requires \valid(pIp->inv + (0..8));
    assigns pIp->inv[0..8], pIp->bAbleInv, *(pIp->ret);
    ensures pIp->bAbleInv == TRUE32 ==> determinant(pIp) != 0.0;
    ensures pIp->bAbleInv == FALSE32 ==> determinant(pIp) == 0.0;
    ensures \forall integer i; 0 <= i < 9 ==> 
            (pIp->bAbleInv == TRUE32 ==> pIp->inv[i] == \old(pIp->inv[i]) / determinant(pIp)) &&
            (pIp->bAbleInv == FALSE32 ==> pIp->inv[i] == \old(pIp->src[i]));
*/
void MatrixInv33FFun(MatrixInv33F *pIp)
{
    siint08 i;
    float32 rank;

    pIp->bAbleInv = FALSE32;

    pIp->inv[0] = pIp->src[4] * pIp->src[8] - pIp->src[5] * pIp->src[7];
    pIp->inv[1] = pIp->src[2] * pIp->src[7] - pIp->src[1] * pIp->src[8];
    pIp->inv[2] = pIp->src[1] * pIp->src[5] - pIp->src[2] * pIp->src[4];
    pIp->inv[3] = pIp->src[5] * pIp->src[6] - pIp->src[3] * pIp->src[8];
    pIp->inv[4] = pIp->src[0] * pIp->src[8] - pIp->src[2] * pIp->src[6];
    pIp->inv[5] = pIp->src[2] * pIp->src[3] - pIp->src[0] * pIp->src[5];
    pIp->inv[6] = pIp->src[3] * pIp->src[7] - pIp->src[4] * pIp->src[6];
    pIp->inv[7] = pIp->src[1] * pIp->src[6] - pIp->src[0] * pIp->src[7];
    pIp->inv[8] = pIp->src[0] * pIp->src[4] - pIp->src[1] * pIp->src[3];

    rank = pIp->src[0] * pIp->inv[0] + pIp->src[1] * pIp->inv[3] + pIp->src[2] * pIp->inv[6];

    if ((FLT32_ZERO < rank) || (rank < -FLT32_ZERO))
    {
        pIp->bAbleInv = TRUE32;

        /*@ loop invariant 0 <= i <= 9;
            loop invariant \forall integer j; 0 <= j < i ==> pIp->inv[j] == pIp->inv[j] / rank;
            loop assigns i, pIp->inv[0..8];
            loop variant 9 - i;
        */
        for (i = 0; i < 9; i++)
        {
            pIp->inv[i] = pIp->inv[i] / rank;
        }
    }
    else
    {
        /*@ loop invariant 0 <= i <= 9;
            loop invariant \forall integer j; 0 <= j < i ==> pIp->inv[j] == pIp->src[j];
            loop assigns i, pIp->inv[0..8];
            loop variant 9 - i;
        */
        for (i = 0; i < 9; i++)
        {
            pIp->inv[i] = pIp->src[i];
        }
    }

    *(pIp->ret) = pIp->bAbleInv;
}
