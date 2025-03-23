#if !defined(__LUAO_CEILLOG2_H__)
#define __LUAO_CEILLOG2_H__

#include "common.h"


#ifndef _cast_byte_
#define _cast_byte_
	#define cast_byte cast(lu_byte, (i))
#endif

#ifndef _lu_byte_
#define _lu_byte_
	typedef unsigned char lu_byte;
#endif


void luaO_ceillog2Fun(void *p);

typedef struct __luaO_ceillog2
{
	/* Functional Interface */
	Fun			fun;
	/* Input Variables */
	unsigned int			x;
	/* Output Variables */
	lu_byte*			ret;
	/* In&Output Variables */
	/* Statement Variables*/
	/* Argument Variables */
} luaO_ceillog2;

#endif // __LUAO_CEILLOG2_H__