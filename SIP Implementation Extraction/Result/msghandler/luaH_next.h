#if !defined(__LUAH_NEXT_H__)
#define __LUAH_NEXT_H__

#include "common.h"
#include "findindex.h"

#ifndef _cast_int_
#define _cast_int_
	#define cast_int cast(int, (i))
#endif

#ifndef _setobj2s_
#define _setobj2s_
	#define setobj2s setobj(L,s2v(o1),o2)
#endif

#ifndef _s2v_
#define _s2v_
	#define s2v (&(o)->val)
#endif

#ifndef _tagisempty_
#define _tagisempty_
	#define tagisempty (novariant(tag) == LUA_TNIL)
#endif

#ifndef _isempty_
#define _isempty_
	#define isempty ttisnil(v)
#endif

#ifndef _setivalue_
#define _setivalue_
	#define setivalue { TValue *io=(obj); val_(io).i=(x); settt_(io, LUA_VNUMINT); }
#endif

#ifndef _getnodekey_
#define _getnodekey_
	#define getnodekey { TValue *io_=(obj); const Node *n_=(node); \
		  io_->value_ = n_->u.key_val; io_->tt_ = n_->u.key_tt; \
		  checkliveness(L,io_); }
#endif

#ifndef _sizenode_
#define _sizenode_
	#define sizenode (twoto((t)->lsizenode))
#endif

#ifndef _gnode_
#define _gnode_
	#define gnode (&(t)->node[i])
#endif

#ifndef _gval_
#define _gval_
	#define gval (&(n)->i_val)
#endif

#ifndef _getArrTag_
#define _getArrTag_
	#define getArrTag (cast(lu_byte*, (t)->array) + sizeof(unsigned) + (k))
#endif

#ifndef _farr2val_
#define _farr2val_
	#define farr2val ((res)->tt_ = tag, (res)->value_ = *getArrVal(h,(k)))
#endif

#ifndef _lua_State_
#define _lua_State_
	struct lua_State;
#endif

#ifndef _lua_Integer_
#define _lua_Integer_
	typedef LUA_INTEGER lua_Integer;
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

#ifndef _Node_
#define _Node_
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

#ifndef _Table_
#define _Table_
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