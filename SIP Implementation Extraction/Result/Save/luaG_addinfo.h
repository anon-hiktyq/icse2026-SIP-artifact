#if !defined(__LUAG_ADDINFO_H__)
#define __LUAG_ADDINFO_H__

#include "common.h"
#include "luaO_chunkid.h"
#include "luaO_pushfstring.h"

#ifndef _LUA_IDSIZE_
	#define LUA_IDSIZE 60
#endif

#ifndef _GETLSTR_
	#define getlstr (strisshr(ts) \
		? (cast_void((len) = cast_sizet((ts)->shrlen)), rawgetshrstr(ts)) \
		: (cast_void((len) = (ts)->u.lnglen), (ts)->contents))
#endif

struct lua_State;
#ifndef _LS_BYTE_
	typedef signed char ls_byte;
#endif

#ifndef _TSTRING_
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
#endif

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

void luaG_addinfoFun(void *p);

typedef struct __luaG_addinfo
{
	/* Functional Interface */
	Fun			fun;
	/* Input Variables */
	int			line;
	/* Output Variables */
	const char *			ret;
	/* In&Output Variables */
	lua_State*			L;
	const char*			msg;
	TString*			src;
	/* Statement Variables*/
	/* Argument Variables */
} luaG_addinfo;

#endif // __LUAG_ADDINFO_H__