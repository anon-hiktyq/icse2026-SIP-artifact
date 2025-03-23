#if !defined(__B_TCPROCESS_H__)
#define __B_TCPROCESS_H__

#include "common.h"
#include "CheckCal.h"

#ifndef _SAM_DAMP_
	#define SAM_DAMP 0x00
#endif

#ifndef _SAM_CRUISE_
	#define SAM_CRUISE 0x33
#endif

#ifndef _NOCTRL_
	#define NOCTRL 0x44
#endif

#ifndef _TR32_FLGMODE_VALUE_
	#define TR32_FLGMODE_VALUE TR32_VALUE(FST_FLGMODE, SND_FLGMODE, TRD_FLGMODE, (x))
#endif

#ifndef _UNINT08_
	typedef unsigned char   unint08;
#endif

#ifndef _UNINT32_
	typedef unsigned long   unint32;
#endif


void B_TcProcessFun(void *p);

typedef struct __B_TcProcess
{
	/* Functional Interface */
	Fun			fun;
	/* Input Variables */
	unint08*			tcaData;
	/* Output Variables */
	/* In&Output Variables */
	/* Statement Variables*/
	/* Argument Variables */
} B_TcProcess;

#endif // __B_TCPROCESS_H__