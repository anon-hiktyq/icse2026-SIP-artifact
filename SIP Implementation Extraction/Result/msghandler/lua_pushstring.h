#if !defined(__LUA_PUSHSTRING_H__)
#define __LUA_PUSHSTRING_H__

#include "common.h"
#include "luaS_new.h"

#ifndef _s2v_
#define _s2v_
	#define s2v (&(o)->val)
#endif

#ifndef _setnilvalue_
#define _setnilvalue_
	#define setnilvalue settt_(obj, LUA_VNIL)
#endif

#ifndef _setsvalue2s_
#define _setsvalue2s_
	#define setsvalue2s setsvalue(L,s2v(o),s)
#endif

#ifndef _getstr_
#define _getstr_
	#define getstr (strisshr(ts) ? rawgetshrstr(ts) : (ts)->contents)
#endif

#ifndef _api_incr_top_
#define _api_incr_top_
	#define api_incr_top (L->top.p++, api_check(L, L->top.p <= L->ci->top.p, "stack overflow"))
#endif

#ifndef _lua_lock_
#define _lua_lock_
	#define lua_lock ((void) 0)
#endif

#ifndef _lua_unlock_
#define _lua_unlock_
	#define lua_unlock ((void) 0)
#endif

#ifndef _luaC_checkGC_
#define _luaC_checkGC_
	#define luaC_checkGC luaC_condGC(L,(void)0,(void)0)
#endif

#ifndef _lua_State_
#define _lua_State_
	struct lua_State;
#endif

#ifndef _l_mem_
#define _l_mem_
	typedef ptrdiff_t l_mem;
#endif

#ifndef _lu_byte_
#define _lu_byte_
	typedef unsigned char lu_byte;
#endif

#ifndef _ls_byte_
#define _ls_byte_
	typedef signed char ls_byte;
#endif

#ifndef _Value_
#define _Value_
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

#ifndef _TValue_
#define _TValue_
	struct TValue {
	  TValuefields;
	};
#endif

#ifndef _StkId_
#define _StkId_
	typedef StackValue *StkId;
#endif

#ifndef _StkIdRel_
#define _StkIdRel_
	union {
	  StkId p;  /* actual pointer */
	  ptrdiff_t offset;  /* used while the stack is being reallocated */
	};
#endif

#ifndef _GCObject_
#define _GCObject_
	struct GCObject {
	  CommonHeader;
	};
#endif

#ifndef _TString_
#define _TString_
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

#ifndef _global_State_
#define _global_State_
	struct global_State {
	  lua_Alloc frealloc;  /* function to reallocate memory */
	  void *ud;         /* auxiliary data to 'frealloc' */
	  l_mem GCtotalbytes;  /* number of bytes currently allocated + debt */
	  l_mem GCdebt;  /* bytes counted but not yet allocated */
	  l_mem GCmarked;  /* number of objects marked in a GC cycle */
	  l_mem GCmajorminor;  /* auxiliary counter to control major-minor shifts */
	  stringtable strt;  /* hash table for strings */
	  TValue l_registry;
	  TValue nilvalue;  /* a nil value */
	  unsigned int seed;  /* randomized seed for hashes */
	  lu_byte gcparams[LUA_GCPN];
	  lu_byte currentwhite;
	  lu_byte gcstate;  /* state of garbage collector */
	  lu_byte gckind;  /* kind of GC running */
	  lu_byte gcstopem;  /* stops emergency collections */
	  lu_byte gcstp;  /* control whether GC is running */
	  lu_byte gcemergency;  /* true if this is an emergency collection */
	  GCObject *allgc;  /* list of all collectable objects */
	  GCObject **sweepgc;  /* current position of sweep in list */
	  GCObject *finobj;  /* list of collectable objects with finalizers */
	  GCObject *gray;  /* list of gray objects */
	  GCObject *grayagain;  /* list of objects to be traversed atomically */
	  GCObject *weak;  /* list of tables with weak values */
	  GCObject *ephemeron;  /* list of ephemeron tables (weak keys) */
	  GCObject *allweak;  /* list of all-weak tables */
	  GCObject *tobefnz;  /* list of userdata to be GC */
	  GCObject *fixedgc;  /* list of objects not to be collected */
	  /* fields for generational collector */
	  GCObject *survival;  /* start of objects that survived one GC cycle */
	  GCObject *old1;  /* start of old1 objects */
	  GCObject *reallyold;  /* objects more than one cycle old ("really old") */
	  GCObject *firstold1;  /* first OLD1 object in the list (if any) */
	  GCObject *finobjsur;  /* list of survival objects with finalizers */
	  GCObject *finobjold1;  /* list of old1 objects with finalizers */
	  GCObject *finobjrold;  /* list of really old objects with finalizers */
	  struct lua_State *twups;  /* list of threads with open upvalues */
	  lua_CFunction panic;  /* to be called in unprotected errors */
	  TString *memerrmsg;  /* message for memory-allocation errors */
	  TString *tmname[TM_N];  /* array with tag-method names */
	  struct Table *mt[LUA_NUMTYPES];  /* metatables for basic types */
	  TString *strcache[STRCACHE_N][STRCACHE_M];  /* cache for strings in API */
	  lua_WarnFunction warnf;  /* warning function */
	  void *ud_warn;         /* auxiliary data to 'warnf' */
	  LX mainth;  /* main thread of this state */
	};
#endif


void lua_pushstringFun(void *p);

typedef struct __lua_pushstring
{
	/* Functional Interface */
	Fun			fun;
	/* Input Variables */
	/* Output Variables */
	const char *			ret;
	/* In&Output Variables */
	lua_State*			L;
	const char*			s;
	/* Statement Variables*/
	/* Argument Variables */
} lua_pushstring;

#endif // __LUA_PUSHSTRING_H__