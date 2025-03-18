#if !defined(__LUAS_HASH_H__)
#define __LUAS_HASH_H__

#include "common.h"


#ifndef _LU_BYTE_
	typedef unsigned char lu_byte;
#endif


#ifndef _CAST_UINT_
	#define cast_uint(i) ((unsigned int) (i))
#endif

#ifndef _CAST_BYTE_
	#define cast_byte(i) ((lu_byte) (i))
#endif



typedef struct __luaS_hash
{
/* 接口函数 */
	void (*fun)( struct __luaS_hash *);
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

void luaS_hashFun(luaS_hash *pIp);
#endif // __LUAS_HASH_H__