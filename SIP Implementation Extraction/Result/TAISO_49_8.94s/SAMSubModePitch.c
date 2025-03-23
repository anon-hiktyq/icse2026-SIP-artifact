#include "SAMSubModePitch.h"
void SAMSubModePitchFun(void *p) 
{
    SAMSubModePitch *pIp = (SAMSubModePitch*)p;

    float32 pirawtmp  ;

    if ( pIp -> pSDS->flgSP == 1 )						   		    	/* ��SP��־Ϊ��̫�� */
    {
		pirawtmp =  fabs( pIp -> pSDS->piyaw )  ;

		if ( pirawtmp > 1.0f )								/* ̫������������ > 1�� */
		{
			pIp -> countPublic++ ;									/* ��ʽ������ */

			if ( pIp -> countPublic > 16 )    						/* ����12TS,��̫���������,תѲ�� */
			{
				TR32_BIAS_WYPI_VALUE( 0.0f ) ;				/* �帩��ƫ�� */

				/* ת��SAMѲ����ʽ */
				flgMode = SAM_CRUISE ;
				TR32_FLGMODE_VALUE(flgMode) ;				/* ��Ѳ����ʽ�� */
				pIp -> countMode = 0 ;								/* ��������ڼ��� */
				pIp -> countPublic = 0 ;							/* ��ʽ������ */
			}
			else
			{
				pIp -> pCtrl[0].Up = 0.0f ;					/* ��������� */
				pIp -> pCtrl[1].Up = 0.0f ;					/* ��������� */
				pIp -> pCtrl[2].Up = 0.0f ;					/* ��������� */

			}
		}
	}
    else
    {
        pIp -> countPublic = 0 ;								     /* ��ʽ������ */
    }

    if (pIp -> countMode > 5625)									 /* ��720��̫���Բ�����,�æ�x=0.5��/��,��y=0��/��,ת�������� */
    {
		flgMode = SAM_ROLL ;
        TR32_FLGMODE_VALUE(flgMode) ;						/* ת��SAM����������ʽ */
        TR32_BIAS_WXRO_VALUE(0.5f) ;
        TR32_BIAS_WYPI_VALUE(0.0f) ;

        pIp -> countMode = 0 ;										/* �������ڼ����� */
        pIp -> countPublic = 0 ;									/* ��ʽ������ */

    }

	return ;
}