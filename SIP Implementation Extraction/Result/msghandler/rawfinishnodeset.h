#if !defined(__RAWFINISHNODESET_H__)
#define __RAWFINISHNODESET_H__

#include "common.h"


#ifndef _cast_
#define _cast_
	#define cast ((t)(exp))
#endif

#ifndef _setobj_
#define _setobj_
	#define setobj { TValue *io1=(obj1); const TValue *io2=(obj2); \
	          io1->value_ = io2->value_; settt_(io1, io2->tt_); \
		  checkliveness(L,io1); lua_assert(!isnonstrictnil(io1)); }
#endif

#ifndef _isabstkey_
#define _isabstkey_
	#define isabstkey checktag((v), LUA_VABSTKEY)
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


void rawfinishnodesetFun(void *p);

typedef struct __rawfinishnodeset
{
	/* Functional Interface */
	Fun			fun;
	/* Input Variables */
	/* Output Variables */
	int*			ret;
	/* In&Output Variables */
	const TValue*			slot;
	TValue*			val;
	/* Statement Variables*/
	/* Argument Variables */
} rawfinishnodeset;

#endif // __RAWFINISHNODESET_H__