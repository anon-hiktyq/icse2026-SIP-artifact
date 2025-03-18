#if !defined(__INSTACK_H__)
#define __INSTACK_H__

#include "common.h"


#ifndef _S2V_
	#define s2v (&(o)->val)
#endif

#ifndef _CALLINFO_
	typedef struct CallInfo CallInfo;
#endif

#ifndef _TVALUE_
	struct TValue {
	  TValuefields;
	};
#endif

#ifndef _STKID_
	typedef StackValue *StkId;
#endif

#ifndef _STKIDREL_
	union {
	  StkId p;  /* actual pointer */
	  ptrdiff_t offset;  /* used while the stack is being reallocated */
	};
#endif


void instackFun(void *p);

typedef struct __instack
{
/* 接口函数 */
	Fun			fun;
/* 输入端口 */
	CallInfo*			ci;
	const TValue*			o;
	/* 输出端口 */
	int*			ret;
	/* 输入输出端口 */
	/* 状态变量 */
	/* 参数变量 */
} instack;

#endif // __INSTACK_H__