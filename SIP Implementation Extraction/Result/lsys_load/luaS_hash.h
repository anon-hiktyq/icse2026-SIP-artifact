#if !defined(__LUAS_HASH_H__)
#define __LUAS_HASH_H__

#include "common.h"


#ifndef _CAST_UINT_
	#define cast_uint cast(unsigned int, (i))
#endif

#ifndef _CAST_BYTE_
	#define cast_byte cast(lu_byte, (i))
#endif


void luaS_hashFun(void *p);

typedef struct __luaS_hash
{
	/* Functional Interface */
	Fun			fun;
	/* Input Variables */
	const char*			str;
	size_t			l;
	unsigned int			seed;
	/* Output Variables */
	unsigned int			h;
	unsigned int*			ret;
	/* In&Output Variables */
	/* Statement Variables*/
	/* Argument Variables */
} luaS_hash;

#endif // __LUAS_HASH_H__