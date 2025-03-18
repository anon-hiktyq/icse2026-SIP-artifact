#if !defined(__LUAH_NEXT_H__)
#define __LUAH_NEXT_H__

#include "common.h"
#include findindex.h

#ifndef _CAST_INT_
	#define cast_int cast(int, (i))
#endif

#ifndef _SETOBJ2S_
	#define setobj2s setobj(L,s2v(o1),o2)
#endif

#ifndef _S2V_
	#define s2v (&(o)->val)
#endif

#ifndef _TAGISEMPTY_
	#define tagisempty (novariant(tag) == LUA_TNIL)
#endif

#ifndef _ISEMPTY_
	#define isempty ttisnil(v)
#endif

#ifndef _SETIVALUE_
	#define setivalue { TValue *io=(obj); val_(io).i=(x); settt_(io, LUA_VNUMINT); }
#endif

#ifndef _GETNODEKEY_
	#define getnodekey { TValue *io_=(obj); const Node *n_=(node); \
		  io_->value_ = n_->u.key_val; io_->tt_ = n_->u.key_tt; \
		  checkliveness(L,io_); }
#endif

#ifndef _SIZENODE_
	#define sizenode (twoto((t)->lsizenode))
#endif

#ifndef _GNODE_
	#define gnode (&(t)->node[i])
#endif

#ifndef _GVAL_
	#define gval (&(n)->i_val)
#endif

#ifndef _GETARRTAG_
	#define getArrTag (cast(lu_byte*, (t)->array) + sizeof(unsigned) + (k))
#endif

#ifndef _FARR2VAL_
	#define farr2val ((res)->tt_ = tag, (res)->value_ = *getArrVal(h,(k)))
#endif

struct lua_State;
#ifndef _LUA_INTEGER_
	typedef LUA_INTEGER lua_Integer;
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

void luaH_nextFun(void *p);

typedef struct __luaH_next
{
	/* Functional Interface */
	Fun			fun;
	/* Input Variables */
	/* Output Variables */
	int*			ret;
	/* In&Output Variables */
	lua_State*			L;
	Table*			t;
	StkId			key;
	/* Statement Variables*/
	/* Argument Variables */
} luaH_next;

#endif // __LUAH_NEXT_H__