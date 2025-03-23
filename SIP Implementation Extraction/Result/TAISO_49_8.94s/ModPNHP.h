#if !defined(__MODPNHP_H__)
#define __MODPNHP_H__

#include "common.h"


#ifndef _FLOAT32_
	typedef float           float32;
#endif


void ModPNHPFun(void *p);

typedef struct __ModPNHP
{
	/* Functional Interface */
	Fun			fun;
	/* Input Variables */
	float32			x;
	float32			halfperiod;
	/* Output Variables */
	float32			npp2;
	float32*			ret;
	/* In&Output Variables */
	/* Statement Variables*/
	/* Argument Variables */
} ModPNHP;

#endif // __MODPNHP_H__