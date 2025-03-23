#if !defined(__LUAO_CODEPARAM_H__)
#define __LUAO_CODEPARAM_H__

#include "common.h"
#include "luaO_ceillog2.h"

#ifndef _cast_
#define _cast_
	#define cast ((t)(exp))
#endif

#ifndef _cast_byte_
#define _cast_byte_
	#define cast_byte cast(lu_byte, (i))
#endif


void luaO_codeparamFun(void *p);

typedef struct __luaO_codeparam
{
	/* Functional Interface */
	Fun			fun;
	/* Input Variables */
	unsigned int			p;
	/* Output Variables */
	lu_byte*			ret;
	/* In&Output Variables */
	/* Statement Variables*/
	/* Argument Variables */
} luaO_codeparam;

#endif // __LUAO_CODEPARAM_H__