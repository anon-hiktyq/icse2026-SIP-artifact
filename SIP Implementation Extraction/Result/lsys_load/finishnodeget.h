#if !defined(__FINISHNODEGET_H__)
#define __FINISHNODEGET_H__

#include "common.h"


#ifndef _TTYPETAG_
	#define ttypetag withvariant(rawtt(o))
#endif

#ifndef _SETOBJ_
	#define setobj { TValue *io1=(obj1); const TValue *io2=(obj2); \
	          io1->value_ = io2->value_; settt_(io1, io2->tt_); \
		  checkliveness(L,io1); lua_assert(!isnonstrictnil(io1)); }
#endif

#ifndef _TTISNIL_
	#define ttisnil checktype((v), LUA_TNIL)
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


void finishnodegetFun(void *p);

typedef struct __finishnodeget
{
	/* Functional Interface */
	Fun			fun;
	/* Input Variables */
	/* Output Variables */
	lu_byte*			ret;
	/* In&Output Variables */
	const TValue*			val;
	TValue*			res;
	/* Statement Variables*/
	/* Argument Variables */
} finishnodeget;

#endif // __FINISHNODEGET_H__