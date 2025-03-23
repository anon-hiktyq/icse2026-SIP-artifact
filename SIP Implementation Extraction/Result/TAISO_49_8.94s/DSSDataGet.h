#if !defined(__DSSDATAGET_H__)
#define __DSSDATAGET_H__

#include "common.h"
#include "Delay.h"
#include "DiviationToFloat.h"

#ifndef _DIVIATION_TO_FLOAT_DSS_
	#define DIVIATION_TO_FLOAT_DSS DiviationToFloat((x), 0xFFF, 0x800, 2.44140625e-3f)
#endif

#ifndef _UNINT08_
	typedef unsigned char   unint08;
#endif

#ifndef _UNINT16_
	typedef unsigned int    unint16;
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


void DSSDataGetFun(void *p);

typedef struct __DSSDataGet
{
	/* Functional Interface */
	Fun			fun;
	/* Input Variables */
	/* Output Variables */
	/* In&Output Variables */
	SDSSData*			pDSSData;
	/* Statement Variables*/
	/* Argument Variables */
} DSSDataGet;

#endif // __DSSDATAGET_H__