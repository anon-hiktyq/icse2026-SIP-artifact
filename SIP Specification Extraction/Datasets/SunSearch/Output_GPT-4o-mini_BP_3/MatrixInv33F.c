
#include "MatrixInv33F.h"

/*@ 
  @ requires pIp != \null;
  @ ensures pIp -> bAbleInv == \result;
  @ assigns pIp -> bAbleInv, pIp -> inv[0..8], pIp -> ret;
  @ ensures (pIp -> bAbleInv == TRUE32) ==> 
  @     (\forall integer i; 0 <= i < 9 ==> pIp -> inv[i] == pIp -> src[i] / rank);
  @ ensures (pIp -> bAbleInv == FALSE32) ==> 
  @     (\forall integer i; 0 <= i < 9 ==> pIp -> inv[i] == pIp -> src[i]);
  @ ensures (FLT32_ZERO < rank || rank < -FLT32_ZERO) ==> 
  @     (pIp -> bAbleInv == TRUE32);
  @ ensures (FLT32_ZERO >= rank && rank <= FLT32_ZERO) ==> 
  @     (pIp -> bAbleInv == FALSE32);
  @ ensures rank == pIp -> src[0] * pIp -> inv[0] + pIp -> src[1] * pIp -> inv[3] + pIp -> src[2] * pIp -> inv[6] ==> 
  @     (FLT32_ZERO < rank || rank < -FLT32_ZERO || pIp -> bAbleInv == FALSE32);
*/
void MatrixInv33FFun(MatrixInv33F *pIp)
{
    siint08 i;
    float32 rank;

    pIp -> bAbleInv = FALSE32;

    pIp -> inv[0] = pIp -> src[4] * pIp -> src[8] - pIp -> src[5] * pIp -> src[7];
    pIp -> inv[1] = pIp -> src[2] * pIp -> src[7] - pIp -> src[1] * pIp -> src[8];
    pIp -> inv[2] = pIp -> src[1] * pIp -> src[5] - pIp -> src[2] * pIp -> src[4];
    pIp -> inv[3] = pIp -> src[5] * pIp -> src[6] - pIp -> src[3] * pIp -> src[8];
    pIp -> inv[4] = pIp -> src[0] * pIp -> src[8] - pIp -> src[2] * pIp -> src[6];
    pIp -> inv[5] = pIp -> src[2] * pIp -> src[3] - pIp -> src[0] * pIp -> src[5];
    pIp -> inv[6] = pIp -> src[3] * pIp -> src[7] - pIp -> src[4] * pIp -> src[6];
    pIp -> inv[7] = pIp -> src[1] * pIp -> src[6] - pIp -> src[0] * pIp -> src[7];
    pIp -> inv[8] = pIp -> src[0] * pIp -> src[4] - pIp -> src[1] * pIp -> src[3];

    rank = pIp -> src[0] * pIp -> inv[0] + pIp -> src[1] * pIp -> inv[3] + pIp -> src[2] * pIp -> inv[6];

    if ((FLT32_ZERO < rank) || (rank < -FLT32_ZERO))
    {
        pIp -> bAbleInv = TRUE32;

        for (i=0; i<9; i++)
        {
            pIp -> inv[i] = pIp -> inv[i] / rank;
        }
    }
    else
    {
        for (i=0; i<9; i++)
        {
            pIp -> inv[i] = pIp -> src[i];
        }
    }

    *(pIp -> ret) = pIp -> bAbleInv;
}
