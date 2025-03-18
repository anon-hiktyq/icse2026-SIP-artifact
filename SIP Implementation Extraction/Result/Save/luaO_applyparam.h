#if !defined(__LUAO_APPLYPARAM_H__)
#define __LUAO_APPLYPARAM_H__

#include "common.h"


#ifndef _MAX_LMEM_
	#define MAX_LMEM cast(l_mem, (cast(lu_mem, 1) << (sizeof(l_mem) * 8 - 1)) - 1)
#endif

#ifndef _L_MEM_
	typedef ptrdiff_t l_mem;
#endif

#ifndef _LU_BYTE_
	typedef unsigned char lu_byte;
#endif


void luaO_applyparamFun(void *p);

typedef struct __luaO_applyparam
{
	/* Functional Interface */
	Fun			fun;
	/* Input Variables */
	lu_byte			p;
	l_mem			x;
	/* Output Variables */
	l_mem*			ret;
	/* In&Output Variables */
	/* Statement Variables*/
	/* Argument Variables */
} luaO_applyparam;

#endif // __LUAO_APPLYPARAM_H__