#if !defined(__FORPREP_H__)
#define __FORPREP_H__

#include "common.h"
#include "luaG_runerror.h"
#include "forlimit.h"
#include "luaG_forerror.h"

#ifndef _l_unlikely_
#define _l_unlikely_
	#define l_unlikely luai_unlikely(x)
#endif

#ifndef _l_castS2U_
#define _l_castS2U_
	#define l_castS2U ((lua_Unsigned)(i))
#endif

#ifndef _l_castU2S_
#define _l_castU2S_
	#define l_castU2S ((lua_Integer)(i))
#endif

#ifndef _luai_numlt_
#define _luai_numlt_
	#define luai_numlt ((a)<(b))
#endif

#ifndef _s2v_
#define _s2v_
	#define s2v (&(o)->val)
#endif

#ifndef _ttisinteger_
#define _ttisinteger_
	#define ttisinteger checktag((o), LUA_VNUMINT)
#endif

#ifndef _ivalue_
#define _ivalue_
	#define ivalue check_exp(ttisinteger(o), val_(o).i)
#endif

#ifndef _setfltvalue_
#define _setfltvalue_
	#define setfltvalue { TValue *io=(obj); val_(io).n=(x); settt_(io, LUA_VNUMFLT); }
#endif

#ifndef _setivalue_
#define _setivalue_
	#define setivalue { TValue *io=(obj); val_(io).i=(x); settt_(io, LUA_VNUMINT); }
#endif

#ifndef _chgivalue_
#define _chgivalue_
	#define chgivalue { TValue *io=(obj); lua_assert(ttisinteger(io)); val_(io).i=(x); }
#endif

#ifndef _tonumber_
#define _tonumber_
	#define tonumber (ttisfloat(o) ? (*(n) = fltvalue(o), 1) : luaV_tonumber_(o,n))
#endif

#ifndef _lua_State_
#define _lua_State_
	struct lua_State;
#endif

#ifndef _lua_Number_
#define _lua_Number_
	typedef LUA_NUMBER lua_Number;
#endif

#ifndef _lua_Integer_
#define _lua_Integer_
	typedef LUA_INTEGER lua_Integer;
#endif

#ifndef _lua_Unsigned_
#define _lua_Unsigned_
	typedef LUA_UNSIGNED lua_Unsigned;
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


void forprepFun(void *p);

typedef struct __forprep
{
	/* Functional Interface */
	Fun			fun;
	/* Input Variables */
	/* Output Variables */
	int*			ret;
	/* In&Output Variables */
	lua_State*			L;
	StkId			ra;
	/* Statement Variables*/
	/* Argument Variables */
} forprep;

#endif // __FORPREP_H__