#if !defined(__LUAG_GETFUNCLINE_H__)
#define __LUAG_GETFUNCLINE_H__

#include "common.h"
#include "getbaseline.h"

#ifndef _LUA_ASSERT_
	#define lua_assert ((void)0)
#endif

#ifndef _ABSLINEINFO_
	#define ABSLINEINFO (-0x80)
#endif

#ifndef _LS_BYTE_
	typedef signed char ls_byte;
#endif

#ifndef _PROTO_
	struct Proto {
	  CommonHeader;
	  lu_byte numparams;  /* number of fixed (named) parameters */
	  lu_byte flag;
	  lu_byte maxstacksize;  /* number of registers needed by this function */
	  int sizeupvalues;  /* size of 'upvalues' */
	  int sizek;  /* size of 'k' */
	  int sizecode;
	  int sizelineinfo;
	  int sizep;  /* size of 'p' */
	  int sizelocvars;
	  int sizeabslineinfo;  /* size of 'abslineinfo' */
	  int linedefined;  /* debug information  */
	  int lastlinedefined;  /* debug information  */
	  TValue *k;  /* constants used by the function */
	  Instruction *code;  /* opcodes */
	  struct Proto **p;  /* functions defined inside the function */
	  Upvaldesc *upvalues;  /* upvalue information */
	  ls_byte *lineinfo;  /* information about source lines (debug information) */
	  AbsLineInfo *abslineinfo;  /* idem */
	  LocVar *locvars;  /* information about local variables (debug information) */
	  TString  *source;  /* used for debug information */
	  GCObject *gclist;
	};
#endif


void luaG_getfunclineFun(void *p);

typedef struct __luaG_getfuncline
{
	/* Functional Interface */
	Fun			fun;
	/* Input Variables */
	const Proto*			f;
	int			pc;
	/* Output Variables */
	int*			ret;
	/* In&Output Variables */
	/* Statement Variables*/
	/* Argument Variables */
} luaG_getfuncline;

#endif // __LUAG_GETFUNCLINE_H__