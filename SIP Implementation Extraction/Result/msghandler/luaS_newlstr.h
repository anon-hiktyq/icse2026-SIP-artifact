#if !defined(__LUAS_NEWLSTR_H__)
#define __LUAS_NEWLSTR_H__

#include "common.h"
#include internshrstr.h
#include luaM_toobig.h
#include luaS_createlngstrobj.h

#ifndef _L_UNLIKELY_
	#define l_unlikely luai_unlikely(x)
#endif

#ifndef _MAX_SIZE_
	#define MAX_SIZE (sizeof(size_t) < sizeof(lua_Integer) ? MAX_SIZET \
				  : cast_sizet(LUA_MAXINTEGER))
#endif

#ifndef _GETLNGSTR_
	#define getlngstr check_exp(!strisshr(ts), (ts)->contents)
#endif

#ifndef _LUAI_MAXSHORTLEN_
	#define LUAI_MAXSHORTLEN 40
#endif

struct lua_State;
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

void luaS_newlstrFun(void *p);

typedef struct __luaS_newlstr
{
	/* Functional Interface */
	Fun			fun;
	/* Input Variables */
	size_t			l;
	/* Output Variables */
	TString *			ret;
	/* In&Output Variables */
	lua_State*			L;
	const char*			str;
	/* Statement Variables*/
	/* Argument Variables */
} luaS_newlstr;

#endif // __LUAS_NEWLSTR_H__