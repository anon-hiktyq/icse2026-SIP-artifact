#if !defined(__REINSERTHASH_H__)
#define __REINSERTHASH_H__

#include "common.h"
#include "newcheckedkey.h"

#ifndef _ISEMPTY_
	#define isempty ttisnil(v)
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

void reinserthashFun(void *p);

typedef struct __reinserthash
{
	/* Functional Interface */
	Fun			fun;
	/* Input Variables */
	Table*			ot;
	/* Output Variables */
	/* In&Output Variables */
	lua_State*			L;
	Table*			t;
	/* Statement Variables*/
	/* Argument Variables */
} reinserthash;

#endif // __REINSERTHASH_H__