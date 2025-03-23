#if !defined(__SAMSUBMODEPITCH_H__)
#define __SAMSUBMODEPITCH_H__

#include "common.h"


#ifndef _SAM_ROLL_
	#define SAM_ROLL 0x22
#endif

#ifndef _SAM_CRUISE_
	#define SAM_CRUISE 0x33
#endif

#ifndef _TR32_FLGMODE_VALUE_
	#define TR32_FLGMODE_VALUE TR32_VALUE(FST_FLGMODE, SND_FLGMODE, TRD_FLGMODE, (x))
#endif

#ifndef _TR32_BIAS_WXRO_VALUE_
	#define TR32_BIAS_WXRO_VALUE TR32_VALUE(FST_BIAS_WXRO, SND_BIAS_WXRO, TRD_BIAS_WXRO, (x))
#endif

#ifndef _TR32_BIAS_WYPI_VALUE_
	#define TR32_BIAS_WYPI_VALUE TR32_VALUE(FST_BIAS_WYPI, SND_BIAS_WYPI, TRD_BIAS_WYPI, (x))
#endif

#ifndef _UNINT08_
	typedef unsigned char   unint08;
#endif

#ifndef _UNINT32_
	typedef unsigned long   unint32;
#endif

#ifndef _FLOAT32_
	typedef float           float32;
#endif

#ifndef _SDSSDATA_
	typedef struct TAG_DSS_DATA
	{	
		unint32     stateFlag_A;			/* ���ݼӵ� */
		unint32     stateFlag_B;			/* ���ݼӵ� */
		float32 	royaw;
		float32 	piyaw;
	    unint32     flgSP;					/* ̫���ɼ���־ */
	}SDSSData;
#endif

#ifndef _SCONTROLLER_
	typedef struct TAG_CONTROLLERIN
	{
	    
	    float32 	Up;						/* ������� */
	    float32 	Ud;						/* ������� */
	    float32 	fy;						/* ��� */
	    
	}SController;
#endif


void SAMSubModePitchFun(void *p);

typedef struct __SAMSubModePitch
{
	/* Functional Interface */
	Fun			fun;
	/* Input Variables */
	const SDSSData*			pSDS;
	unint32			countPublic;
	unint32			countMode;
	/* Output Variables */
	/* In&Output Variables */
	SController*			pCtrl;
	/* Statement Variables*/
	/* Argument Variables */
} SAMSubModePitch;

#endif // __SAMSUBMODEPITCH_H__