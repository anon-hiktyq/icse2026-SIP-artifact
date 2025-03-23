#if !defined(__SAMSUBMODEDAMP_H__)
#define __SAMSUBMODEDAMP_H__

#include "common.h"
#include "TripleFabsMax.h"

#ifndef _SAM_PITCH_
	#define SAM_PITCH 0x11
#endif

#ifndef _TR32_FLGMODE_VALUE_
	#define TR32_FLGMODE_VALUE TR32_VALUE(FST_FLGMODE, SND_FLGMODE, TRD_FLGMODE, (x))
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


void SAMSubModeDampFun(void *p);

typedef struct __SAMSubModeDamp
{
	/* Functional Interface */
	Fun			fun;
	/* Input Variables */
	const float32*			rate;
	const float32			max;
	unint32			countPublic;
	unint32			countMode;
	/* Output Variables */
	/* In&Output Variables */
	/* Statement Variables*/
	/* Argument Variables */
} SAMSubModeDamp;

#endif // __SAMSUBMODEDAMP_H__