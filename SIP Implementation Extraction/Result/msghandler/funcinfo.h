#if !defined(__FUNCINFO_H__)
#define __FUNCINFO_H__

#include "common.h"
#include luaO_chunkid.h

#ifndef _LL_
	#define LL (sizeof(x)/sizeof(char) - 1)
#endif

#ifndef _GETLSTR_
	#define getlstr (strisshr(ts) \
		? (cast_void((len) = cast_sizet((ts)->shrlen)), rawgetshrstr(ts)) \
		: (cast_void((len) = (ts)->u.lnglen), (ts)->contents))
#endif

#ifndef _LUACLOSURE_
	#define LuaClosure ((f) != NULL && (f)->c.tt == LUA_VLCL)
#endif

#ifndef _LUA_DEBUG_
	struct lua_Debug;
#endif

#ifndef _LU_BYTE_
	typedef unsigned char lu_byte;
#endif

typedef signed char ls_byte;
struct TString {
  CommonHeader;
  lu_byte extra;  /* reserved words for short strings; "has hash" for longs */
  ls_byte shrlen;  /* length for short strings, negative for long strings */
  unsigned int hash;
  union {
    size_t lnglen;  /* length for long strings */
    struct TString *hnext;  /* linked list for hash table */
  } u;
  char *contents;  /* pointer to content in long strings */
  lua_Alloc falloc;  /* deallocation function for external strings */
  void *ud;  /* user data for external strings */
};
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
#ifndef _CCLOSURE_
	struct CClosure {
	  ClosureHeader;
	  lua_CFunction f;
	  TValue upvalue[1];  /* list of upvalues */
	};
#endif

struct LClosure {
  ClosureHeader;
  struct Proto *p;
  UpVal *upvals[1];  /* list of upvalues */
};
union Closure {
  CClosure c;
  LClosure l;
};

void funcinfoFun(void *p);

typedef struct __funcinfo
{
	/* Functional Interface */
	Fun			fun;
	/* Input Variables */
	/* Output Variables */
	/* In&Output Variables */
	lua_Debug*			ar;
	Closure*			cl;
	/* Statement Variables*/
	/* Argument Variables */
} funcinfo;

#endif // __FUNCINFO_H__