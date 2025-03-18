#if !defined(__LUAO_APPLYPARAM_H__)
#define __LUAO_APPLYPARAM_H__

#include "common.h"


#ifndef _L_MEM_
	typedef ptrdiff_t l_mem;
#endif

#ifndef _LU_BYTE_
	typedef unsigned char lu_byte;
#endif



typedef struct __luaO_applyparam
{
/* 接口函数 */
	void (*fun)( struct __luaO_applyparam *);
/* 输入端口 */
	lu_byte			p;
	l_mem			x;
	/* 输出端口 */
	l_mem*			ret;
	/* 输入输出端口 */
	/* 状态变量 */
	/* 参数变量 */
} luaO_applyparam;

void luaO_applyparamFun(luaO_applyparam *pIp);
#endif // __LUAO_APPLYPARAM_H__