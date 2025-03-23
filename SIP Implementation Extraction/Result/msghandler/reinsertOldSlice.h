#if !defined(__REINSERTOLDSLICE_H__)
#define __REINSERTOLDSLICE_H__

#include "common.h"
#include "insertkey.h"

#ifndef _l_castU2S_
#define _l_castU2S_
	#define l_castU2S ((lua_Integer)(i))
#endif

#ifndef _tagisempty_
#define _tagisempty_
	#define tagisempty (novariant(tag) == LUA_TNIL)
#endif

#ifndef _setivalue_
#define _setivalue_
	#define setivalue { TValue *io=(obj); val_(io).i=(x); settt_(io, LUA_VNUMINT); }
#endif

#ifndef _getArrTag_
#define _getArrTag_
	#define getArrTag (cast(lu_byte*, (t)->array) + sizeof(unsigned) + (k))
#endif

#ifndef _farr2val_
#define _farr2val_
	#define farr2val ((res)->tt_ = tag, (res)->value_ = *getArrVal(h,(k)))
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


void reinsertOldSliceFun(void *p);

typedef struct __reinsertOldSlice
{
	/* Functional Interface */
	Fun			fun;
	/* Input Variables */
	unsigned int			oldasize;
	unsigned int			newasize;
	/* Output Variables */
	/* In&Output Variables */
	Table*			t;
	/* Statement Variables*/
	/* Argument Variables */
} reinsertOldSlice;

#endif // __REINSERTOLDSLICE_H__