#if !defined(__SWITCHSS_H__)
#define __SWITCHSS_H__

#include "common.h"


#ifndef _UNINT32_
	typedef unsigned long   unint32;
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


void SwitchSSFun(void *p);

typedef struct __SwitchSS
{
	/* Functional Interface */
	Fun			fun;
	/* Input Variables */
	/* Output Variables */
	/* In&Output Variables */
	/* Statement Variables*/
	/* Argument Variables */
	SDSSData			mDSSData;
} SwitchSS;

#endif // __SWITCHSS_H__