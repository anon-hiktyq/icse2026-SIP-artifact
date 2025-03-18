#if !defined(__SAVE_H__)
#define __SAVE_H__

#include "common.h"
#include "lexerror.h"

#define MAX_SIZE (sizeof(size_t) < sizeof(lua_Integer) ? MAX_SIZET \
			  : cast_sizet(LUA_MAXINTEGER))
#define cast_char cast(char, (i))
#define luaZ_sizebuffer ((buff)->buffsize)
#define luaZ_bufflen ((buff)->n)
#define luaZ_resizebuffer ((buff)->buffer = luaM_reallocvchar(L, (buff)->buffer, \
				(buff)->buffsize, size), \
	(buff)->buffsize = size)
struct Mbuffer {
  char *buffer;
  size_t n;
  size_t buffsize;
};

void saveFun(void *p);

typedef struct __save
{
	/* Functional Interface */
	Fun			fun;
	/* Input Variables */
	int			c;
	/* Output Variables */
	/* In&Output Variables */
	LexState*			ls;
	/* Statement Variables*/
	/* Argument Variables */
} save;

#endif // __SAVE_H__