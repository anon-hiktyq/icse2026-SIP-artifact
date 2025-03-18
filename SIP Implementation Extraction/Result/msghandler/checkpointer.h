#if !defined(__CHECKPOINTER_H__)
#define __CHECKPOINTER_H__

#include "common.h"


struct GCObject {
  CommonHeader;
};

void checkpointerFun(void *p);

typedef struct __checkpointer
{
	/* Functional Interface */
	Fun			fun;
	/* Input Variables */
	/* Output Variables */
	/* In&Output Variables */
	GCObject**			p;
	GCObject*			o;
	/* Statement Variables*/
	/* Argument Variables */
} checkpointer;

#endif // __CHECKPOINTER_H__