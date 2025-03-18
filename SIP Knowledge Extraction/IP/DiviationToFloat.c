#include "DiviationToFloat.h"
void DiviationToFloatFun(void *p)
{
    DiviationToFloat *pIp = (DiviationToFloat*)p;

    pIp -> fresult = ((siint16)((pIp -> input & pIp -> mask) - pIp -> offset)) * pIp -> LSB ;

    *(pIp -> ret) = pIp -> fresult;
}