#include "DiviationToFloat.h"
void DiviationToFloatFun(DiviationToFloat *pIp)
{

    pIp -> fresult = ((siint16)((pIp -> input & pIp -> mask) - pIp -> offset)) * pIp -> LSB ;

    *(pIp -> ret) = pIp -> fresult;
}