#if !defined(__SETNODEVECTOR_H__)
#define __SETNODEVECTOR_H__

#include "common.h"
#include "luaO_ceillog2.h"
#include "luaG_runerror.h"
#include "luaM_malloc_.h"

#ifndef _CAST_
	#define cast ((t)(exp))
#endif

#ifndef _CAST_INT_
	#define cast_int cast(int, (i))
#endif

#ifndef _CAST_BYTE_
	#define cast_byte cast(lu_byte, (i))
#endif

#ifndef _SETEMPTY_
	#define setempty settt_(v, LUA_VEMPTY)
#endif

#ifndef _SETNILKEY_
	#define setnilkey (keytt(node) = LUA_TNIL)
#endif

#ifndef _TWOTO_
	#define twoto (1u<<(x))
#endif

#ifndef _LUAM_NEWVECTOR_
	#define luaM_newvector cast(t*, luaM_malloc_(L, cast_sizet(n)*sizeof(t), 0))
#endif

#ifndef _LUAM_NEWBLOCK_
	#define luaM_newblock luaM_newvector(L, size, char)
#endif

#ifndef _GNODE_
	#define gnode (&(t)->node[i])
#endif

#ifndef _GVAL_
	#define gval (&(n)->i_val)
#endif

#ifndef _GNEXT_
	#define gnext ((n)->u.next)
#endif

#ifndef _SETNODUMMY_
	#define setnodummy ((t)->flags &= NOTBITDUMMY)
#endif

#ifndef _SETDUMMY_
	#define setdummy ((t)->flags |= BITDUMMY)
#endif

#ifndef _LIMFORLAST_
	#define LIMFORLAST 3
#endif

#ifndef _GETLASTFREE_
	#define getlastfree ((cast(Limbox *, (t)->node) - 1)->lastfree)
#endif

#ifndef _MAXHBITS_
	#define MAXHBITS (MAXABITS - 1)
#endif

#ifndef _MAXHSIZE_
	#define MAXHSIZE luaM_limitN(1 << MAXHBITS, Node)
#endif

#ifndef _DUMMYNODE_
	#define dummynode (&dummynode_)
#endif

struct lua_State;
#ifndef _LU_BYTE_
	typedef unsigned char lu_byte;
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

void setnodevectorFun(void *p);

typedef struct __setnodevector
{
	/* Functional Interface */
	Fun			fun;
	/* Input Variables */
	unsigned int			size;
	/* Output Variables */
	/* In&Output Variables */
	lua_State*			L;
	Table*			t;
	/* Statement Variables*/
	/* Argument Variables */
} setnodevector;

#endif // __SETNODEVECTOR_H__