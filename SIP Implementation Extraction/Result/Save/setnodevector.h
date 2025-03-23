#if !defined(__SETNODEVECTOR_H__)
#define __SETNODEVECTOR_H__

#include "common.h"
#include "luaO_ceillog2.h"
#include "luaG_runerror.h"
#include "luaM_malloc_.h"

#ifndef _cast_
#define _cast_
	#define cast ((t)(exp))
#endif

#ifndef _cast_int_
#define _cast_int_
	#define cast_int cast(int, (i))
#endif

#ifndef _cast_byte_
#define _cast_byte_
	#define cast_byte cast(lu_byte, (i))
#endif

#ifndef _setempty_
#define _setempty_
	#define setempty settt_(v, LUA_VEMPTY)
#endif

#ifndef _setnilkey_
#define _setnilkey_
	#define setnilkey (keytt(node) = LUA_TNIL)
#endif

#ifndef _twoto_
#define _twoto_
	#define twoto (1u<<(x))
#endif

#ifndef _luaM_newvector_
#define _luaM_newvector_
	#define luaM_newvector cast(t*, luaM_malloc_(L, cast_sizet(n)*sizeof(t), 0))
#endif

#ifndef _luaM_newblock_
#define _luaM_newblock_
	#define luaM_newblock luaM_newvector(L, size, char)
#endif

#ifndef _gnode_
#define _gnode_
	#define gnode (&(t)->node[i])
#endif

#ifndef _gval_
#define _gval_
	#define gval (&(n)->i_val)
#endif

#ifndef _gnext_
#define _gnext_
	#define gnext ((n)->u.next)
#endif

#ifndef _setnodummy_
#define _setnodummy_
	#define setnodummy ((t)->flags &= NOTBITDUMMY)
#endif

#ifndef _setdummy_
#define _setdummy_
	#define setdummy ((t)->flags |= BITDUMMY)
#endif

#ifndef _LIMFORLAST_
#define _LIMFORLAST_
	#define LIMFORLAST 3
#endif

#ifndef _getlastfree_
#define _getlastfree_
	#define getlastfree ((cast(Limbox *, (t)->node) - 1)->lastfree)
#endif

#ifndef _MAXHBITS_
#define _MAXHBITS_
	#define MAXHBITS (MAXABITS - 1)
#endif

#ifndef _MAXHSIZE_
#define _MAXHSIZE_
	#define MAXHSIZE luaM_limitN(1 << MAXHBITS, Node)
#endif

#ifndef _dummynode_
#define _dummynode_
	#define dummynode (&dummynode_)
#endif

#ifndef _lua_State_
#define _lua_State_
	struct lua_State;
#endif

#ifndef _lu_byte_
#define _lu_byte_
	typedef unsigned char lu_byte;
#endif

#ifndef _TValue_
#define _TValue_
	struct TValue {
	  TValuefields;
	};
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