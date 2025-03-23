#if !defined(__TRAVERSETHREAD_H__)
#define __TRAVERSETHREAD_H__

#include "common.h"
#include "reallymarkobject.h"
#include "luaD_shrinkstack.h"

#ifndef _lua_assert_
#define _lua_assert_
	#define lua_assert ((void)0)
#endif

#ifndef _s2v_
#define _s2v_
	#define s2v (&(o)->val)
#endif

#ifndef _setnilvalue_
#define _setnilvalue_
	#define setnilvalue settt_(obj, LUA_VNIL)
#endif

#ifndef _EXTRA_STACK_
#define _EXTRA_STACK_
	#define EXTRA_STACK 5
#endif

#ifndef _isintwups_
#define _isintwups_
	#define isintwups (L->twups != L)
#endif

#ifndef _GCSpropagate_
#define _GCSpropagate_
	#define GCSpropagate 0
#endif

#ifndef _GCSatomic_
#define _GCSatomic_
	#define GCSatomic 2
#endif

#ifndef _isold_
#define _isold_
	#define isold (getage(o) > G_SURVIVAL)
#endif

#ifndef _markvalue_
#define _markvalue_
	#define markvalue { checkliveness(mainthread(g),o); \
	  if (valiswhite(o)) reallymarkobject(g,gcvalue(o)); }
#endif

#ifndef _markobject_
#define _markobject_
	#define markobject { if (iswhite(t)) reallymarkobject(g, obj2gco(t)); }
#endif

#ifndef _linkgclist_
#define _linkgclist_
	#define linkgclist linkgclist_(obj2gco(o), &(o)->gclist, &(p))
#endif

#ifndef _lua_State_
#define _lua_State_
	struct lua_State;
#endif

#ifndef _lu_byte_
#define _lu_byte_
	typedef unsigned char lu_byte;
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

#ifndef _UpVal_
#define _UpVal_
	struct UpVal {
	  CommonHeader;
	  union {
	    TValue *p;  /* points to stack or to its own value */
	    ptrdiff_t offset;  /* used while the stack is being reallocated */
	  } v;
	  union {
	    struct {  /* (when open) */
	      struct UpVal *next;  /* linked list */
	      struct UpVal **previous;
	    } open;
	    TValue value;  /* the value (when closed) */
	  } u;
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

#ifndef _LX_
#define _LX_
	struct LX {
	  lu_byte extra_[LUA_EXTRASPACE];
	  lua_State l;
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


void traversethreadFun(void *p);

typedef struct __traversethread
{
	/* Functional Interface */
	Fun			fun;
	/* Input Variables */
	/* Output Variables */
	l_mem*			ret;
	/* In&Output Variables */
	global_State*			g;
	lua_State*			th;
	/* Statement Variables*/
	/* Argument Variables */
} traversethread;

#endif // __TRAVERSETHREAD_H__