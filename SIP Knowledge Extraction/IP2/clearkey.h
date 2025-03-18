#if !defined(__CLEARKEY_H__)
#define __CLEARKEY_H__

#include "common.h"


#ifndef _LUA_ASSERT_
	#define lua_assert ((void)0)
#endif

#ifndef _ISEMPTY_
	#define isempty ttisnil(v)
#endif

#ifndef _KEYISCOLLECTABLE_
	#define keyiscollectable (keytt(n) & BIT_ISCOLLECTABLE)
#endif

#ifndef _SETDEADKEY_
	#define setdeadkey (keytt(node) = LUA_TDEADKEY)
#endif

#ifndef _GVAL_
	#define gval (&(n)->i_val)
#endif

#ifndef _LU_BYTE_
	typedef unsigned char lu_byte;
#endif

#ifndef _NODE_
	union Node {
	  struct NodeKey {
	    TValuefields;  /* fields for value */
	    lu_byte key_tt;  /* key type */
	    int next;  /* for chaining */
	    Value key_val;  /* key value */
	  } u;
	  TValue i_val;  /* direct access to node's value as a proper 'TValue' */
	};
#endif


void clearkeyFun(void *p);

typedef struct __clearkey
{
/* 接口函数 */
	Fun			fun;
/* 输入端口 */
	/* 输出端口 */
	/* 输入输出端口 */
	Node*			n;
	/* 状态变量 */
	/* 参数变量 */
} clearkey;

#endif // __CLEARKEY_H__