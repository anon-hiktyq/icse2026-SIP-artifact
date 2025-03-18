#if !defined(__LUAV_CONCAT_H__)
#define __LUAV_CONCAT_H__

#include "common.h"
#include "luaT_tryconcatTM.h"
#include "luaO_tostring.h"
#include "luaG_runerror.h"
#include "copy2buff.h"
#include "luaS_newlstr.h"
#include "luaS_createlngstrobj.h"

#ifndef _L_UNLIKELY_
	#define l_unlikely luai_unlikely(x)
#endif

#ifndef _MAX_SIZE_
	#define MAX_SIZE (sizeof(size_t) < sizeof(lua_Integer) ? MAX_SIZET \
				  : cast_sizet(LUA_MAXINTEGER))
#endif

#ifndef _CAST_VOID_
	#define cast_void cast(void, (i))
#endif

#ifndef _SETOBJS2S_
	#define setobjs2s setobj(L,s2v(o1),s2v(o2))
#endif

#ifndef _S2V_
	#define s2v (&(o)->val)
#endif

#ifndef _TTISSTRING_
	#define ttisstring checktype((o), LUA_TSTRING)
#endif

#ifndef _TSVALUE_
	#define tsvalue check_exp(ttisstring(o), gco2ts(val_(o).gc))
#endif

#ifndef _SETSVALUE2S_
	#define setsvalue2s setsvalue(L,s2v(o),s)
#endif

#ifndef _GETLNGSTR_
	#define getlngstr check_exp(!strisshr(ts), (ts)->contents)
#endif

#ifndef _TSSLEN_
	#define tsslen (strisshr(ts) ? cast_sizet((ts)->shrlen) : (ts)->u.lnglen)
#endif

#ifndef _LUAI_MAXSHORTLEN_
	#define LUAI_MAXSHORTLEN 40
#endif

#ifndef _CVT2STR_
	#define cvt2str 0
#endif

#ifndef _TOSTRING_
	#define tostring (ttisstring(o) || (cvt2str(o) && (luaO_tostring(L, o), 1)))
#endif

#ifndef _ISEMPTYSTR_
	#define isemptystr (ttisshrstring(o) && tsvalue(o)->shrlen == 0)
#endif

struct lua_State;
#ifndef _LU_BYTE_
	typedef unsigned char lu_byte;
#endif

#ifndef _LS_BYTE_
	typedef signed char ls_byte;
#endif

#ifndef _VALUE_
	union Value {
	  struct GCObject *gc;    /* collectable objects */
	  void *p;         /* light userdata */
	  lua_CFunction f; /* light C functions */
	  lua_Integer i;   /* integer numbers */
	  lua_Number n;    /* float numbers */
	  /* not used, but may avoid warnings for uninitialized value */
	  lu_byte ub;
	};
#endif

#ifndef _TVALUE_
	struct TValue {
	  TValuefields;
	};
#endif

#ifndef _STKID_
	typedef StackValue *StkId;
#endif

#ifndef _STKIDREL_
	union {
	  StkId p;  /* actual pointer */
	  ptrdiff_t offset;  /* used while the stack is being reallocated */
	};
#endif

#ifndef _GCOBJECT_
	struct GCObject {
	  CommonHeader;
	};
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

#ifndef _LUA_STATE_
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


void luaV_concatFun(void *p);

typedef struct __luaV_concat
{
	/* Functional Interface */
	Fun			fun;
	/* Input Variables */
	int			total;
	/* Output Variables */
	/* In&Output Variables */
	lua_State*			L;
	/* Statement Variables*/
	/* Argument Variables */
} luaV_concat;

#endif // __LUAV_CONCAT_H__