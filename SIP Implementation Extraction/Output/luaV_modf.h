#if !defined(__LUAV_MODF_H__)
#define __LUAV_MODF_H__

#include "common.h"


#ifndef _LUAI_NUMMOD_
	#define luai_nummod { (void)L; (m) = l_mathop(fmod)(a,b); \
	    if (((m) > 0) ? (b) < 0 : ((m) < 0 && (b) > 0)) (m) += (b); }
#endif

struct lua_State;
#ifndef _LUA_NUMBER_
	typedef LUA_NUMBER lua_Number;
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

void luaV_modfFun(void *p);

typedef struct __luaV_modf
{
	/* Functional Interface */
	Fun			fun;
	/* Input Variables */
	lua_State*			L;
	lua_Number			m;
	lua_Number			n;
	/* Output Variables */
	lua_Number*			ret;
	/* In&Output Variables */
	/* Statement Variables*/
	/* Argument Variables */
} luaV_modf;

#endif // __LUAV_MODF_H__