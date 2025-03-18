#if !defined(__LUAF_UNLINKUPVAL_H__)
#define __LUAF_UNLINKUPVAL_H__

#include "common.h"


#ifndef _LUA_ASSERT_
	#define lua_assert ((void)0)
#endif

#ifndef _UPISOPEN_
	#define upisopen ((up)->v.p != &(up)->u.value)
#endif

#ifndef _UPVAL_
	struct UpVal {
	  CommonHeader;
	  union {
	    TValue *p;  /* points to stack or to its own value */
	    ptrdiff_t offset;  /* used while the stack is being reallocated */
	  } v;
	  union {
	    struct {  /* (when open) */
	      struct UpVal *next;  /* linked list */
	      struct UpVal **previous;
	    } open;
	    TValue value;  /* the value (when closed) */
	  } u;
	};
#endif


void luaF_unlinkupvalFun(void *p);

typedef struct __luaF_unlinkupval
{
/* 接口函数 */
	Fun			fun;
/* 输入端口 */
	/* 输出端口 */
	/* 输入输出端口 */
	UpVal*			uv;
	/* 状态变量 */
	/* 参数变量 */
} luaF_unlinkupval;

#endif // __LUAF_UNLINKUPVAL_H__