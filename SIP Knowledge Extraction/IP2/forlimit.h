#if !defined(__FORLIMIT_H__)
#define __FORLIMIT_H__

#include "common.h"
#include luaV_tointeger.h
#include luaG_forerror.h

#ifndef _LUA_MAXINTEGER_
	#define LUA_MAXINTEGER _I64_MAX
#endif

#ifndef _LUA_MININTEGER_
	#define LUA_MININTEGER _I64_MIN
#endif

#ifndef _LUAI_NUMLT_
	#define luai_numlt ((a)<(b))
#endif

#ifndef _TONUMBER_
	#define tonumber (ttisfloat(o) ? (*(n) = fltvalue(o), 1) : luaV_tonumber_(o,n))
#endif

struct lua_State;
#ifndef _LUA_NUMBER_
	typedef LUA_NUMBER lua_Number;
#endif

#ifndef _LUA_INTEGER_
	typedef LUA_INTEGER lua_Integer;
#endif

#ifndef _LU_BYTE_
	typedef unsigned char lu_byte;
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
#ifndef _F2IMOD_
	enum {
	  F2Ieq,     /* no rounding; accepts only integral values */
	  F2Ifloor,  /* takes the floor of the number */
	  F2Iceil    /* takes the ceiling of the number */
	};
#endif


void forlimitFun(void *p);

typedef struct __forlimit
{
/* 接口函数 */
	Fun			fun;
/* 输入端口 */
	lua_Integer			init;
	lua_Integer			step;
	/* 输出端口 */
	int*			ret;
	/* 输入输出端口 */
	lua_State*			L;
	const TValue*			lim;
	lua_Integer*			p;
	/* 状态变量 */
	/* 参数变量 */
} forlimit;

#endif // __FORLIMIT_H__