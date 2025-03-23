#include "DiviationToFloat.h"
void DiviationToFloatFun(void *p) 
{
    DiviationToFloat *pIp = (DiviationToFloat*)p;

    float32 pIp -> fresult ;		                                /* �ֲ����� */

    pIp -> fresult = ((siint16)((pIp -> input & pIp -> mask) - pIp -> offset)) * pIp -> LSB ;	/* LSBΪ��С���� */

    *(pIp -> ret) = fresult ;
}