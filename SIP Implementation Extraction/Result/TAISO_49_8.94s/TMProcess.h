#if !defined(__TMPROCESS_H__)
#define __TMPROCESS_H__

#include "common.h"
#include "CheckCal16.h"
#include "SendUartData.h"

#ifndef _TR32_FLGMODE_
	#define TR32_FLGMODE Tr32Uint08(FST_FLGMODE, SND_FLGMODE, TRD_FLGMODE)
#endif

#ifndef _UI32_HIHI8_
	#define UI32_HIHI8 (((ui32) >> 24) & MASK_LO08)
#endif

#ifndef _UI32_HILO8_
	#define UI32_HILO8 (((ui32) >> 16) & MASK_LO08)
#endif

#ifndef _UI32_LOHI8_
	#define UI32_LOHI8 (((ui32) >>  8) & MASK_LO08)
#endif

#ifndef _UI32_LOLO8_
	#define UI32_LOLO8 (((ui32)      ) & MASK_LO08)
#endif

#ifndef _UI16_HI8_
	#define UI16_HI8 (((ui16) >>  8) & MASK_LO08)
#endif

#ifndef _UI16_LO8_
	#define UI16_LO8 (((ui16)      ) & MASK_LO08)
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

#ifndef _SATTITUDE_
	typedef struct TAG_ATTITUDE_PARA     	
	{                                    	
		                                 	
		float32 	angle[3];			 	/* ������̬�� */
		float32 	rate[3]; 			 	/* ������ٶ� */
		                                 	
	}SAttitude;
#endif


void TMProcessFun(void *p);

typedef struct __TMProcess
{
	/* Functional Interface */
	Fun			fun;
	/* Input Variables */
	unint32			countSate;
	SAttitude			mAttitude;
	/* Output Variables */
	/* In&Output Variables */
	/* Statement Variables*/
	/* Argument Variables */
} TMProcess;

#endif // __TMPROCESS_H__