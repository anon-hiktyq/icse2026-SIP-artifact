#include "SAMSubModePitch.h"
void SAMSubModePitchFun(SAMSubModePitch *pIp)
{

    float32 pirawtmp  ;

    if ( pIp -> pSDS->flgSP == 1 )
    {
		pirawtmp =  fabs( pIp -> pSDS->piyaw )  ;

		if ( pirawtmp > 1.0f )
		{
			pIp -> countPublic++ ;

			if ( pIp -> countPublic > 16 )
			{
				TR32_BIAS_WYPI_VALUE( 0.0f ) ;

				pIp->flgMode = SAM_CRUISE ;
				TR32_FLGMODE_VALUE(pIp->flgMode) ;
				pIp -> countMode = 0 ;
				pIp -> countPublic = 0 ;
			}
			else
			{
				pIp -> pCtrl[0].Up = 0.0f ;
				pIp -> pCtrl[1].Up = 0.0f ;
				pIp -> pCtrl[2].Up = 0.0f ;

			}
		}
	}
    else
    {
        pIp -> countPublic = 0 ;
    }

    if (pIp -> countMode > 5625)
    {
		pIp->flgMode = SAM_ROLL ;
        TR32_FLGMODE_VALUE(pIp->flgMode) ;
        TR32_BIAS_WXRO_VALUE(0.5f) ;
        TR32_BIAS_WYPI_VALUE(0.0f) ;

        pIp -> countMode = 0 ;
        pIp -> countPublic = 0 ;

    }

	return ;
}