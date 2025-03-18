#if !defined(__TRYFUNCTM_H__)
#define __TRYFUNCTM_H__

#include "common.h"
#include luaT_gettmbyobj.h
#include luaG_callerror.h
#include luaG_runerror.h

#ifndef _L_UNLIKELY_
	#define l_unlikely luai_unlikely(x)
#endif

#ifndef _SETOBJS2S_
	#define setobjs2s setobj(L,s2v(o1),s2v(o2))
#endif

#ifndef _SETOBJ2S_
	#define setobj2s setobj(L,s2v(o1),o2)
#endif

#ifndef _S2V_
	#define s2v (&(o)->val)
#endif

#ifndef _TTISNIL_
	#define ttisnil checktype((v), LUA_TNIL)
#endif

#ifndef _CIST_CCMT_
	#define CIST_CCMT 8
#endif

#ifndef _MAX_CCMT_
	#define MAX_CCMT (0xfu << CIST_CCMT)
#endif

struct lua_State;
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

#ifndef _STKID_
	typedef StackValue *StkId;
#endif

#ifndef _STKIDREL_
	union {
	  StkId p;  /* actual pointer */
	  ptrdiff_t offset;  /* used while the stack is being reallocated */
	};
#endif

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

void tryfuncTMFun(void *p);

typedef struct __tryfuncTM
{
/* 接口函数 */
	Fun			fun;
/* 输入端口 */
	unsigned int			status;
	/* 输出端口 */
	unsigned int*			ret;
	/* 输入输出端口 */
	lua_State*			L;
	StkId			func;
	/* 状态变量 */
	/* 参数变量 */
} tryfuncTM;

#endif // __TRYFUNCTM_H__