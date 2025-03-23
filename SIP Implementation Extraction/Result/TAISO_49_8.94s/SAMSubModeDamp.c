#include "SAMSubModeDamp.h"
void SAMSubModeDampFun(void *p) 
{
    SAMSubModeDamp *pIp = (SAMSubModeDamp*)p;

    float32 fabsmax ;										/* ��ʱ������ֵ��� */

    {float32 TripleFabsMax_ret_0;IPCALL(TripleFabsMax,ipTripleFabsMax_0,.fx1 = rate[0],.fy2 = rate[1],.fz3 = rate[2],.ret = &TripleFabsMax_ret_0);fabsmax = TripleFabsMax_ret_0;};	/* ��������̬���ٶ����ֵ */

    if ( fabsmax < pIp -> max )		 							/* ������̬���ٶȾ�С��0.15��/�� */
    {
        pIp -> countPublic++ ;										/* ��ʽ������ */
    }

    /* ��700Ts���ٶȶ�С��0.07��/s �� �����������ʱ�����128��ʱ,�ø������ٶ�ƫ��Ϊ-0.5��/s, ת�븩������ */
    if (( pIp -> countPublic > 350 ) || ( pIp -> countMode > 1000 ))
    {
		flgMode = SAM_PITCH ;
        TR32_FLGMODE_VALUE(flgMode) ;						/* ת�븩��������ʽ */
        TR32_BIAS_WYPI_VALUE(-0.5f) ;						/* ������ƫ��0.5�� */

        pIp -> countMode = 0 ;									    /* ��������ڼ����� */
        pIp -> countPublic = 0 ;									/* ��ʽ������ */
    }

    return ;
}