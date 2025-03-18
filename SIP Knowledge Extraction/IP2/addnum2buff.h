#if !defined(__ADDNUM2BUFF_H__)
#define __ADDNUM2BUFF_H__

#include "common.h"
#include luaO_tostringbuff.h
#include addstr2buff.h

#ifndef _LUA_N2SBUFFSZ_
	#define LUA_N2SBUFFSZ 64
#endif

#ifndef _TVALUE_
	struct TValue {
	  TValuefields;
	};
#endif

#ifndef _BUFFFS_
	struct BuffFS {
	  lua_State *L;
	  char *b;
	  size_t buffsize;
	  size_t blen;  /* length of string in 'buff' */
	  int err;
	  char space[BUFVFS];  /* initial buffer */
	};
#endif


void addnum2buffFun(void *p);

typedef struct __addnum2buff
{
/* 接口函数 */
	Fun			fun;
/* 输入端口 */
	TValue*			num;
	/* 输出端口 */
	/* 输入输出端口 */
	BuffFS*			buff;
	/* 状态变量 */
	/* 参数变量 */
} addnum2buff;

#endif // __ADDNUM2BUFF_H__