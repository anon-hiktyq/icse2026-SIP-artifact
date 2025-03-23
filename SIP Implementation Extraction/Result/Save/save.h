#if !defined(__SAVE_H__)
#define __SAVE_H__

#include "common.h"
#include "lexerror.h"

#ifndef _MAX_SIZE_
#define _MAX_SIZE_
	#define MAX_SIZE (sizeof(size_t) < sizeof(lua_Integer) ? MAX_SIZET \
				  : cast_sizet(LUA_MAXINTEGER))
#endif

#ifndef _cast_char_
#define _cast_char_
	#define cast_char cast(char, (i))
#endif

#ifndef _luaZ_sizebuffer_
#define _luaZ_sizebuffer_
	#define luaZ_sizebuffer ((buff)->buffsize)
#endif

#ifndef _luaZ_bufflen_
#define _luaZ_bufflen_
	#define luaZ_bufflen ((buff)->n)
#endif

#ifndef _luaZ_resizebuffer_
#define _luaZ_resizebuffer_
	#define luaZ_resizebuffer ((buff)->buffer = luaM_reallocvchar(L, (buff)->buffer, \
					(buff)->buffsize, size), \
		(buff)->buffsize = size)
#endif

#ifndef _lua_State_
#define _lua_State_
	struct lua_State;
#endif

#ifndef _Mbuffer_
#define _Mbuffer_
	struct Mbuffer {
	  char *buffer;
	  size_t n;
	  size_t buffsize;
	};
#endif

#ifndef _lua_State_
#define _lua_State_
	struct lua_State {
	  CommonHeader;
	  lu_byte allowhook;
	  TStatus status;
	  StkIdRel top;  /* first free slot in the stack */
	  struct global_State *l_G;
	  CallInfo *ci;  /* call info for current function */
	  StkIdRel stack_last;  /* end of stack (last element + 1) */
	  StkIdRel stack;  /* stack base */
	  UpVal *openupval;  /* list of open upvalues in this stack */
	  StkIdRel tbclist;  /* list of to-be-closed variables */
	  GCObject *gclist;
	  struct lua_State *twups;  /* list of threads with open upvalues */
	  struct lua_longjmp *errorJmp;  /* current error recover point */
	  CallInfo base_ci;  /* CallInfo for first level (C host) */
	  volatile lua_Hook hook;
	  ptrdiff_t errfunc;  /* current error handling function (stack index) */
	  l_uint32 nCcalls;  /* number of nested non-yieldable or C calls */
	  int oldpc;  /* last pc traced */
	  int nci;  /* number of items in 'ci' list */
	  int basehookcount;
	  int hookcount;
	  volatile l_signalT hookmask;
	  struct {  /* info about transferred values (for call/return hooks) */
	    int ftransfer;  /* offset of first value transferred */
	    int ntransfer;  /* number of values transferred */
	  } transferinfo;
	};
#endif

#ifndef _LexState_
#define _LexState_
	struct LexState {
	  int current;  /* current character (charint) */
	  int linenumber;  /* input line counter */
	  int lastline;  /* line of last token 'consumed' */
	  Token t;  /* current token */
	  Token lookahead;  /* look ahead token */
	  struct FuncState *fs;  /* current function (parser) */
	  struct lua_State *L;
	  ZIO *z;  /* input stream */
	  Mbuffer *buff;  /* buffer for tokens */
	  Table *h;  /* to avoid collection/reuse strings */
	  struct Dyndata *dyd;  /* dynamic structures used by the parser */
	  TString *source;  /* current source name */
	  TString *envn;  /* environment variable name */
	};
#endif


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