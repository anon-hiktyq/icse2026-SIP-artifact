#if !defined(__FINISHNODEGET_H__)
#define __FINISHNODEGET_H__

#include "common.h"


#ifndef _ttypetag_
#define _ttypetag_
	#define ttypetag withvariant(rawtt(o))
#endif

#ifndef _setobj_
#define _setobj_
	#define setobj { TValue *io1=(obj1); const TValue *io2=(obj2); \
	          io1->value_ = io2->value_; settt_(io1, io2->tt_); \
		  checkliveness(L,io1); lua_assert(!isnonstrictnil(io1)); }
#endif

#ifndef _ttisnil_
#define _ttisnil_
	#define ttisnil checktype((v), LUA_TNIL)
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