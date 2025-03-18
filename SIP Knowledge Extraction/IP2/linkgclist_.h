#if !defined(__LINKGCLIST__H__)
#define __LINKGCLIST__H__

#include "common.h"


#ifndef _LUA_ASSERT_
	#define lua_assert ((void)0)
#endif

#ifndef _ISGRAY_
	#define isgray (!testbits((x)->marked, WHITEBITS | bitmask(BLACKBIT)))
#endif

#ifndef _SET2GRAY_
	#define set2gray resetbits(x->marked, maskcolors)
#endif

#ifndef _LU_BYTE_
	typedef unsigned char lu_byte;
#endif

#ifndef _GCOBJECT_
	struct GCObject {
	  CommonHeader;
	};
#endif


void linkgclist_Fun(void *p);

typedef struct __linkgclist_
{
/* 接口函数 */
	Fun			fun;
/* 输入端口 */
	/* 输出端口 */
	/* 输入输出端口 */
	GCObject*			o;
	GCObject**			pnext;
	GCObject**			list;
	/* 状态变量 */
	/* 参数变量 */
} linkgclist_;

#endif // __LINKGCLIST__H__