#if !defined(__LUAO_UTF8ESC_H__)
#define __LUAO_UTF8ESC_H__

#include "common.h"


#ifndef _lua_assert_
#define _lua_assert_
	#define lua_assert ((void)0)
#endif

#ifndef _cast_char_
#define _cast_char_
	#define cast_char cast(char, (i))
#endif

#ifndef _UTF8BUFFSZ_
#define _UTF8BUFFSZ_
	#define UTF8BUFFSZ 8
#endif


void luaO_utf8escFun(void *p);

typedef struct __luaO_utf8esc
{
	/* Functional Interface */
	Fun			fun;
	/* Input Variables */
	unsigned long			x;
	/* Output Variables */
	int*			ret;
	/* In&Output Variables */
	char*			buff;
	/* Statement Variables*/
	/* Argument Variables */
} luaO_utf8esc;

#endif // __LUAO_UTF8ESC_H__