#if !defined(__ADDNUM2BUFF_H__)
#define __ADDNUM2BUFF_H__

#include "common.h"
#include "luaO_tostringbuff.h"
#include "addstr2buff.h"

#ifndef _LUA_N2SBUFFSZ_
#define _LUA_N2SBUFFSZ_
	#define LUA_N2SBUFFSZ 64
#endif

#ifndef _TValue_
#define _TValue_
	struct TValue {
	  TValuefields;
	};
#endif

#ifndef _BuffFS_
#define _BuffFS_
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
	/* Functional Interface */
	Fun			fun;
	/* Input Variables */
	TValue*			num;
	/* Output Variables */
	/* In&Output Variables */
	BuffFS*			buff;
	/* Statement Variables*/
	/* Argument Variables */
} addnum2buff;

#endif // __ADDNUM2BUFF_H__