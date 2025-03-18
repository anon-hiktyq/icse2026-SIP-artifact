#if !defined(__LUAV_EQUALOBJ_H__)
#define __LUAV_EQUALOBJ_H__

#include "common.h"
#include luaV_tointegerns.h
#include luaV_tointegerns.h
#include luaS_eqlngstr.h
#include luaT_gettm.h
#include luaT_gettm.h
#include luaT_callTMres.h

#ifndef _LUA_TNUMBER_
	#define LUA_TNUMBER 3
#endif

#ifndef _LUAI_NUMEQ_
	#define luai_numeq ((a)==(b))
#endif

#ifndef _TTYPETAG_
	#define ttypetag withvariant(rawtt(o))
#endif

#ifndef _TTYPE_
	#define ttype (novariant(rawtt(o)))
#endif

#ifndef _LUA_VNIL_
	#define LUA_VNIL makevariant(LUA_TNIL, 0)
#endif

#ifndef _LUA_VFALSE_
	#define LUA_VFALSE makevariant(LUA_TBOOLEAN, 0)
#endif

#ifndef _LUA_VTRUE_
	#define LUA_VTRUE makevariant(LUA_TBOOLEAN, 1)
#endif

#ifndef _TAGISFALSE_
	#define tagisfalse ((t) == LUA_VFALSE || novariant(t) == LUA_TNIL)
#endif

#ifndef _GCVALUE_
	#define gcvalue check_exp(iscollectable(o), val_(o).gc)
#endif

#ifndef _LUA_VNUMINT_
	#define LUA_VNUMINT makevariant(LUA_TNUMBER, 0)
#endif

#ifndef _LUA_VNUMFLT_
	#define LUA_VNUMFLT makevariant(LUA_TNUMBER, 1)
#endif

#ifndef _FLTVALUE_
	#define fltvalue check_exp(ttisfloat(o), val_(o).n)
#endif

#ifndef _IVALUE_
	#define ivalue check_exp(ttisinteger(o), val_(o).i)
#endif

#ifndef _LUA_VSHRSTR_
	#define LUA_VSHRSTR makevariant(LUA_TSTRING, 0)
#endif

#ifndef _LUA_VLNGSTR_
	#define LUA_VLNGSTR makevariant(LUA_TSTRING, 1)
#endif

#ifndef _TSVALUE_
	#define tsvalue check_exp(ttisstring(o), gco2ts(val_(o).gc))
#endif

#ifndef _LUA_VLIGHTUSERDATA_
	#define LUA_VLIGHTUSERDATA makevariant(LUA_TLIGHTUSERDATA, 0)
#endif

#ifndef _LUA_VUSERDATA_
	#define LUA_VUSERDATA makevariant(LUA_TUSERDATA, 0)
#endif

#ifndef _PVALUE_
	#define pvalue check_exp(ttislightuserdata(o), val_(o).p)
#endif

#ifndef _UVALUE_
	#define uvalue check_exp(ttisfulluserdata(o), gco2u(val_(o).gc))
#endif

#ifndef _LUA_VLCF_
	#define LUA_VLCF makevariant(LUA_TFUNCTION, 1)
#endif

#ifndef _FVALUE_
	#define fvalue check_exp(ttislcf(o), val_(o).f)
#endif

#ifndef _LUA_VTABLE_
	#define LUA_VTABLE makevariant(LUA_TTABLE, 0)
#endif

#ifndef _HVALUE_
	#define hvalue check_exp(ttistable(o), gco2t(val_(o).gc))
#endif

#ifndef _FASTTM_
	#define fasttm gfasttm(G(l), mt, e)
#endif

#ifndef _EQSHRSTR_
	#define eqshrstr check_exp((a)->tt == LUA_VSHRSTR, (a) == (b))
#endif

struct lua_State;
#ifndef _LUA_NUMBER_
	typedef LUA_NUMBER lua_Number;
#endif

#ifndef _LUA_INTEGER_
	typedef LUA_INTEGER lua_Integer;
#endif

#ifndef _LUA_CFUNCTION_
	typedef int (*lua_CFunction) (lua_State *L);
#endif

#ifndef _LU_BYTE_
	typedef unsigned char lu_byte;
#endif

union Value {
  struct GCObject *gc;    /* collectable objects */
  void *p;         /* light userdata */
  lua_CFunction f; /* light C functions */
  lua_Integer i;   /* integer numbers */
  lua_Number n;    /* float numbers */
  /* not used, but may avoid warnings for uninitialized value */
  lu_byte ub;
};
struct TValue {
  TValuefields;
};
typedef StackValue *StkId;
union {
  StkId p;  /* actual pointer */
  ptrdiff_t offset;  /* used while the stack is being reallocated */
};
struct GCObject {
  CommonHeader;
};
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
#ifndef _UDATA_
	struct Udata {
	  CommonHeader;
	  unsigned short nuvalue;  /* number of user values */
	  size_t len;  /* number of bytes */
	  struct Table *metatable;
	  GCObject *gclist;
	  UValue uv[1];  /* user values */
	};
#endif

struct Table {
  CommonHeader;
  lu_byte flags;  /* 1<<p means tagmethod(p) is not present */
  lu_byte lsizenode;  /* log2 of number of slots of 'node' array */
  unsigned int asize;  /* number of slots in 'array' array */
  Value *array;  /* array part */
  Node *node;
  struct Table *metatable;
  GCObject *gclist;
};
#ifndef _TMS_
	enum {
	  TM_INDEX,
	  TM_NEWINDEX,
	  TM_GC,
	  TM_MODE,
	  TM_LEN,
	  TM_EQ,  /* last tag method with fast access */
	  TM_ADD,
	  TM_SUB,
	  TM_MUL,
	  TM_MOD,
	  TM_POW,
	  TM_DIV,
	  TM_IDIV,
	  TM_BAND,
	  TM_BOR,
	  TM_BXOR,
	  TM_SHL,
	  TM_SHR,
	  TM_UNM,
	  TM_BNOT,
	  TM_LT,
	  TM_LE,
	  TM_CONCAT,
	  TM_CALL,
	  TM_CLOSE,
	  TM_N		/* number of elements in the enum */
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
#ifndef _GLOBAL_STATE_
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

#ifndef _F2IMOD_
	enum {
	  F2Ieq,     /* no rounding; accepts only integral values */
	  F2Ifloor,  /* takes the floor of the number */
	  F2Iceil    /* takes the ceiling of the number */
	};
#endif


void luaV_equalobjFun(void *p);

typedef struct __luaV_equalobj
{
	/* Functional Interface */
	Fun			fun;
	/* Input Variables */
	/* Output Variables */
	int*			ret;
	/* In&Output Variables */
	lua_State*			L;
	const TValue*			t1;
	const TValue*			t2;
	/* Statement Variables*/
	/* Argument Variables */
} luaV_equalobj;

#endif // __LUAV_EQUALOBJ_H__