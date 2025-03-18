#if !defined(__FINDINDEX_H__)
#define __FINDINDEX_H__

#include "common.h"
#include keyinarray.h
#include getgeneric.h
#include luaG_runerror.h

#ifndef _L_UNLIKELY_
	#define l_unlikely luai_unlikely(x)
#endif

#ifndef _CAST_UINT_
	#define cast_uint cast(unsigned int, (i))
#endif

#ifndef _TTISNIL_
	#define ttisnil checktype((v), LUA_TNIL)
#endif

#ifndef _ISABSTKEY_
	#define isabstkey checktag((v), LUA_VABSTKEY)
#endif

#ifndef _GNODE_
	#define gnode (&(t)->node[i])
#endif

#ifndef _NODEFROMVAL_
	#define nodefromval cast(Node *, (v))
#endif

struct lua_State;
#ifndef _LU_BYTE_
	typedef unsigned char lu_byte;
#endif

struct TValue {
  TValuefields;
};
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

void findindexFun(void *p);

typedef struct __findindex
{
	/* Functional Interface */
	Fun			fun;
	/* Input Variables */
	unsigned int			asize;
	/* Output Variables */
	unsigned int*			ret;
	/* In&Output Variables */
	lua_State*			L;
	Table*			t;
	TValue*			key;
	/* Statement Variables*/
	/* Argument Variables */
} findindex;

#endif // __FINDINDEX_H__