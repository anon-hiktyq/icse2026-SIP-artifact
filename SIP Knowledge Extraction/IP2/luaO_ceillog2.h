#if !defined(__LUAO_CEILLOG2_H__)
#define __LUAO_CEILLOG2_H__

#include "common.h"


#ifndef _CAST_BYTE_
	#define cast_byte cast(lu_byte, (i))
#endif

#ifndef _LU_BYTE_
	typedef unsigned char lu_byte;
#endif


void luaO_ceillog2Fun(void *p);

typedef struct __luaO_ceillog2
{
/* 接口函数 */
	Fun			fun;
/* 输入端口 */
	unsigned int			x;
	/* 输出端口 */
	lu_byte*			ret;
	/* 输入输出端口 */
	/* 状态变量 */
	/* 参数变量 */
} luaO_ceillog2;

#endif // __LUAO_CEILLOG2_H__