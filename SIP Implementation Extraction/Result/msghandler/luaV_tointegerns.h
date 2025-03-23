#if !defined(__LUAV_TOINTEGERNS_H__)
#define __LUAV_TOINTEGERNS_H__

#include "common.h"
#include "luaV_flttointeger.h"

#ifndef _ttisfloat_
#define _ttisfloat_
	#define ttisfloat checktag((o), LUA_VNUMFLT)
#endif

#ifndef _ttisinteger_
#define _ttisinteger_
	#define ttisinteger checktag((o), LUA_VNUMINT)
#endif

#ifndef _fltvalue_
#define _fltvalue_
	#define fltvalue check_exp(ttisfloat(o), val_(o).n)
#endif

#ifndef _ivalue_
#define _ivalue_
	#define ivalue check_exp(ttisinteger(o), val_(o).i)
#endif

#ifndef _lua_Number_
#define _lua_Number_
	typedef LUA_NUMBER lua_Number;
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

#ifndef _F2Imod_
#define _F2Imod_
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