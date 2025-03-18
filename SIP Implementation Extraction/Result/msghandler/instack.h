#if !defined(__INSTACK_H__)
#define __INSTACK_H__

#include "common.h"


#ifndef _S2V_
	#define s2v (&(o)->val)
#endif

#ifndef _CALLINFO_
	typedef struct CallInfo CallInfo;
#endif

struct TValue {
  TValuefields;
};
typedef StackValue *StkId;
union {
  StkId p;  /* actual pointer */
  ptrdiff_t offset;  /* used while the stack is being reallocated */
};

void instackFun(void *p);

typedef struct __instack
{
	/* Functional Interface */
	Fun			fun;
	/* Input Variables */
	CallInfo*			ci;
	const TValue*			o;
	/* Output Variables */
	int*			ret;
	/* In&Output Variables */
	/* Statement Variables*/
	/* Argument Variables */
} instack;

#endif // __INSTACK_H__