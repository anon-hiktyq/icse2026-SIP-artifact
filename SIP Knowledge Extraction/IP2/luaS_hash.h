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
/* 接口函数 */
	Fun			fun;
/* 输入端口 */
	const char*			str;
	size_t			l;
	unsigned int			seed;
	/* 输出端口 */
	unsigned int			h;
	unsigned int*			ret;
	/* 输入输出端口 */
	/* 状态变量 */
	/* 参数变量 */
} luaS_hash;

#endif // __LUAS_HASH_H__