#if !defined(__HGETSTR_H__)
#define __HGETSTR_H__

#include "common.h"
#include luaH_Hgetshortstr.h
#include Hgetlongstr.h

typedef signed char ls_byte;

void HgetstrFun(void *p);

typedef struct __Hgetstr
{
	/* Functional Interface */
	Fun			fun;
	/* Input Variables */
	/* Output Variables */
	const TValue *			ret;
	/* In&Output Variables */
	Table*			t;
	TString*			key;
	/* Statement Variables*/
	/* Argument Variables */
} Hgetstr;

#endif // __HGETSTR_H__