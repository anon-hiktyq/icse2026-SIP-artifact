#include "MatrixInv33F.h"
void MatrixInv33FFun(void *p)
{
    MatrixInv33F *pIp = (MatrixInv33F*)p;

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