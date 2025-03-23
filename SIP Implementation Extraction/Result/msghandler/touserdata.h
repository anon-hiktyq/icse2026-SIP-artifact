#if !defined(__TOUSERDATA_H__)
#define __TOUSERDATA_H__

#include "common.h"


#ifndef _LUA_TLIGHTUSERDATA_
#define _LUA_TLIGHTUSERDATA_
	#define LUA_TLIGHTUSERDATA 2
#endif

#ifndef _LUA_TUSERDATA_
#define _LUA_TUSERDATA_
	#define LUA_TUSERDATA 7
#endif

#ifndef _ttype_
#define _ttype_
	#define ttype (novariant(rawtt(o)))
#endif

#ifndef _pvalue_
#define _pvalue_
	#define pvalue check_exp(ttislightuserdata(o), val_(o).p)
#endif

#ifndef _uvalue_
#define _uvalue_
	#define uvalue check_exp(ttisfulluserdata(o), gco2u(val_(o).gc))
#endif

#ifndef _getudatamem_
#define _getudatamem_
	#define getudatamem (cast_charp(u) + udatamemoffset((u)->nuvalue))
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

#ifndef _GCObject_
#define _GCObject_
	struct GCObject {
	  CommonHeader;
	};
#endif

#ifndef _Udata_
#define _Udata_
	struct Udata {
	  CommonHeader;
	  unsigned short nuvalue;  /* number of user values */
	  size_t len;  /* number of bytes */
	  struct Table *metatable;
	  GCObject *gclist;
	  UValue uv[1];  /* user values */
	};
#endif


void touserdataFun(void *p);

typedef struct __touserdata
{
	/* Functional Interface */
	Fun			fun;
	/* Input Variables */
	const TValue*			o;
	/* Output Variables */
	void *			ret;
	/* In&Output Variables */
	/* Statement Variables*/
	/* Argument Variables */
} touserdata;

#endif // __TOUSERDATA_H__