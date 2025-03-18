#if !defined(__LUAH_FINISHSET_H__)
#define __LUAH_FINISHSET_H__

#include "common.h"
#include "luaG_runerror.h"
#include "luaV_flttointeger.h"
#include "luaH_newkey.h"

#ifndef _L_UNLIKELY_
	#define l_unlikely luai_unlikely(x)
#endif

#ifndef _LUA_ASSERT_
	#define lua_assert ((void)0)
#endif

#ifndef _CAST_UINT_
	#define cast_uint cast(unsigned int, (i))
#endif

#ifndef _LUAI_NUMISNAN_
	#define luai_numisnan (!luai_numeq((a), (a)))
#endif

#ifndef _SETOBJ2T_
	#define setobj2t setobj
#endif

#ifndef _TTISNIL_
	#define ttisnil checktype((v), LUA_TNIL)
#endif

#ifndef _TTISFLOAT_
	#define ttisfloat checktag((o), LUA_VNUMFLT)
#endif

#ifndef _FLTVALUE_
	#define fltvalue check_exp(ttisfloat(o), val_(o).n)
#endif

#ifndef _SETIVALUE_
	#define setivalue { TValue *io=(obj); val_(io).i=(x); settt_(io, LUA_VNUMINT); }
#endif

#ifndef _GNODE_
	#define gnode (&(t)->node[i])
#endif

#ifndef _GVAL_
	#define gval (&(n)->i_val)
#endif

#ifndef _HOK_
	#define HOK 0
#endif

#ifndef _HNOTFOUND_
	#define HNOTFOUND 1
#endif

#ifndef _HFIRSTNODE_
	#define HFIRSTNODE 3
#endif

#ifndef _OBJ2ARR_
	#define obj2arr (*getArrTag(h,(k)) = (val)->tt_, *getArrVal(h,(k)) = (val)->value_)
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

#ifndef _NODE_
	union Node {
	  struct NodeKey {
	    TValuefields;  /* fields for value */
	    lu_byte key_tt;  /* key type */
	    int next;  /* for chaining */
	    Value key_val;  /* key value */
	  } u;
	  TValue i_val;  /* direct access to node's value as a proper 'TValue' */
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


void luaH_finishsetFun(void *p);

typedef struct __luaH_finishset
{
	/* Functional Interface */
	Fun			fun;
	/* Input Variables */
	int			hres;
	/* Output Variables */
	/* In&Output Variables */
	lua_State*			L;
	Table*			t;
	const TValue*			key;
	TValue*			value;
	/* Statement Variables*/
	/* Argument Variables */
} luaH_finishset;

#endif // __LUAH_FINISHSET_H__