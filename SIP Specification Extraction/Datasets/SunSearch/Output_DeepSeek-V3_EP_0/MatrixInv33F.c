
#include "MatrixInv33F.h"

/*@ axiomatic MatrixInv33F {
      logic float32 determinant(float32* src) reads src[0..8];
      axiom determinant_def:
        \forall float32* src; determinant(src) ==
          src[0] * (src[4] * src[8] - src[5] * src[7]) -
          src[1] * (src[3] * src[8] - src[5] * src[6]) +
          src[2] * (src[3] * src[7] - src[4] * src[6]);
    }
*/

/*@ requires \valid(pIp);
    requires \valid(pIp->src + (0..8));
    requires \valid(pIp->inv + (0..8));
    requires \valid(pIp->ret);
    ensures pIp->bAbleInv == TRUE32 ==> determinant(pIp->src) != 0.0;
    ensures pIp->bAbleInv == FALSE32 ==> determinant(pIp->src) == 0.0;
    assigns pIp->inv[0..8], pIp->bAbleInv, *(pIp->ret);
*/
void MatrixInv33FFun(MatrixInv33F *pIp)
{
    siint08 i;
    float32 rank;

    pIp->bAbleInv = FALSE32;

    /*@ assigns pIp->inv[0..8];
        ensures pIp->inv[0] == pIp->src[4] * pIp->src[8] - pIp->src[5] * pIp->src[7];
        ensures pIp->inv[1] == pIp->src[2] * pIp->src[7] - pIp->src[1] * pIp->src[8];
        ensures pIp->inv[2] == pIp->src[1] * pIp->src[5] - pIp->src[2] * pIp->src[4];
        ensures pIp->inv[3] == pIp->src[5] * pIp->src[6] - pIp->src[3] * pIp->src[8];
        ensures pIp->inv[4] == pIp->src[0] * pIp->src[8] - pIp->src[2] * pIp->src[6];
        ensures pIp->inv[5] == pIp->src[2] * pIp->src[3] - pIp->src[0] * pIp->src[5];
        ensures pIp->inv[6] == pIp->src[3] * pIp->src[7] - pIp->src[4] * pIp->src[6];
        ensures pIp->inv[7] == pIp->src[1] * pIp->src[6] - pIp->src[0] * pIp->src[7];
        ensures pIp->inv[8] == pIp->src[0] * pIp->src[4] - pIp->src[1] * pIp->src[3];
    */
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
            loop assigns pIp->inv[0..8];
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
            loop assigns pIp->inv[0..8];
            loop variant 9 - i;
        */
        for (i = 0; i < 9; i++)
        {
            pIp->inv[i] = pIp->src[i];
        }
    }

    *(pIp->ret) = pIp->bAbleInv;
}
