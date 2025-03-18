#if !defined(__FINDLAST_H__)
#define __FINDLAST_H__

#include "common.h"


#ifndef _GCOBJECT_
	struct GCObject {
	  CommonHeader;
	};
#endif


void findlastFun(void *p);

typedef struct __findlast
{
	/* Functional Interface */
	Fun			fun;
	/* Input Variables */
	/* Output Variables */
	GCObject **			ret;
	/* In&Output Variables */
	GCObject**			p;
	/* Statement Variables*/
	/* Argument Variables */
} findlast;

#endif // __FINDLAST_H__