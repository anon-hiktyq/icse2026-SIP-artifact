#if !defined(__INSTACK_H__)
#define __INSTACK_H__

#include "common.h"


#ifndef _s2v_
#define _s2v_
	#define s2v (&(o)->val)
#endif

#ifndef _CallInfo_
#define _CallInfo_
	typedef struct CallInfo CallInfo;
#endif

#ifndef _TValue_
#define _TValue_
	struct TValue {
	  TValuefields;
	};
#endif

#ifndef _StkId_
#define _StkId_
	typedef StackValue *StkId;
#endif

#ifndef _StkIdRel_
#define _StkIdRel_
	union {
	  StkId p;  /* actual pointer */
	  ptrdiff_t offset;  /* used while the stack is being reallocated */
	};
#endif


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