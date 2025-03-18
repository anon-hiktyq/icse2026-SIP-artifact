#if !defined(__LUAV_TOINTEGERNS_H__)
#define __LUAV_TOINTEGERNS_H__

#include "common.h"
#include "luaV_flttointeger.h"

#ifndef _TTISFLOAT_
	#define ttisfloat checktag((o), LUA_VNUMFLT)
#endif

#ifndef _TTISINTEGER_
	#define ttisinteger checktag((o), LUA_VNUMINT)
#endif

#ifndef _FLTVALUE_
	#define fltvalue check_exp(ttisfloat(o), val_(o).n)
#endif

#ifndef _IVALUE_
	#define ivalue check_exp(ttisinteger(o), val_(o).i)
#endif

#ifndef _LUA_NUMBER_
	typedef LUA_NUMBER lua_Number;
#endif

#ifndef _LUA_INTEGER_
	typedef LUA_INTEGER lua_Integer;
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

#ifndef _F2IMOD_
	enum {
	  F2Ieq,     /* no rounding; accepts only integral values */
	  F2Ifloor,  /* takes the floor of the number */
	  F2Iceil    /* takes the ceiling of the number */
	};
#endif


void luaV_tointegernsFun(void *p);

typedef struct __luaV_tointegerns
{
	/* Functional Interface */
	Fun			fun;
	/* Input Variables */
	const TValue*			obj;
	F2Imod			mode;
	/* Output Variables */
	int*			ret;
	/* In&Output Variables */
	lua_Integer*			p;
	/* Statement Variables*/
	/* Argument Variables */
} luaV_tointegerns;

#endif // __LUAV_TOINTEGERNS_H__