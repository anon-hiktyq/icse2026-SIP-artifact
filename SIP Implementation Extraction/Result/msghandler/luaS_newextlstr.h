#if !defined(__LUAS_NEWEXTLSTR_H__)
#define __LUAS_NEWEXTLSTR_H__

#include "common.h"
#include f_pintern.h
#include luaD_rawrunprotected.h
#include f_newext.h
#include luaD_rawrunprotected.h

#ifndef _LUA_OK_
	#define LUA_OK 0
#endif

#ifndef _CAST_VOIDP_
	#define cast_voidp cast(void *, (i))
#endif

#ifndef _CAST_CHARP_
	#define cast_charp cast(char *, (i))
#endif

#ifndef _LSTRFIX_
	#define LSTRFIX -2
#endif

#ifndef _LSTRMEM_
	#define LSTRMEM -3
#endif

#ifndef _LUAM_ERROR_
	#define luaM_error luaD_throw(L, LUA_ERRMEM)
#endif

#ifndef _LUAI_MAXSHORTLEN_
	#define LUAI_MAXSHORTLEN 40
#endif

struct lua_State;
#ifndef _LUA_ALLOC_
	typedef void * (*lua_Alloc) (void *ud, void *ptr, size_t osize, size_t nsize);
#endif

typedef signed char ls_byte;
#ifndef _TSTATUS_
	typedef lu_byte TStatus;
#endif

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
#ifndef _NEWEXT_
	struct NewExt {
	  ls_byte kind;
	  const char *s;
	   size_t len;
	  TString *ts;  /* output */
	};
#endif


void luaS_newextlstrFun(void *p);

typedef struct __luaS_newextlstr
{
	/* Functional Interface */
	Fun			fun;
	/* Input Variables */
	size_t			len;
	/* Output Variables */
	TString *			ret;
	/* In&Output Variables */
	lua_State*			L;
	const char*			s;
	lua_Alloc			falloc;
	Unknown type*			ud;
	/* Statement Variables*/
	/* Argument Variables */
} luaS_newextlstr;

#endif // __LUAS_NEWEXTLSTR_H__