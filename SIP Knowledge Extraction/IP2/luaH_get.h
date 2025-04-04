#if !defined(__LUAH_GET_H__)
#define __LUAH_GET_H__

#include "common.h"
#include luaH_Hgetshortstr.h
#include luaH_getint.h
#include luaV_flttointeger.h
#include getgeneric.h
#include finishnodeget.h

#ifndef _TTYPETAG_
	#define ttypetag withvariant(rawtt(o))
#endif

#ifndef _LUA_VNIL_
	#define LUA_VNIL makevariant(LUA_TNIL, 0)
#endif

#ifndef _LUA_VNUMINT_
	#define LUA_VNUMINT makevariant(LUA_TNUMBER, 0)
#endif

#ifndef _LUA_VNUMFLT_
	#define LUA_VNUMFLT makevariant(LUA_TNUMBER, 1)
#endif

#ifndef _FLTVALUE_
	#define fltvalue check_exp(ttisfloat(o), val_(o).n)
#endif

#ifndef _IVALUE_
	#define ivalue check_exp(ttisinteger(o), val_(o).i)
#endif

#ifndef _LUA_VSHRSTR_
	#define LUA_VSHRSTR makevariant(LUA_TSTRING, 0)
#endif

#ifndef _TSVALUE_
	#define tsvalue check_exp(ttisstring(o), gco2ts(val_(o).gc))
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

#ifndef _GCOBJECT_
	struct GCObject {
	  CommonHeader;
	};
#endif

#ifndef _TSTRING_
	struct TString {
	  CommonHeader;
	  lu_byte extra;  /* reserved words for short strings; "has hash" for longs */
	  ls_byte shrlen;  /* length for short strings, negative for long strings */
	  unsigned int hash;
	  union {
	    size_t lnglen;  /* length for long strings */
	    struct TString *hnext;  /* linked list for hash table */
	  } u;
	  char *contents;  /* pointer to content in long strings */
	  lua_Alloc falloc;  /* deallocation function for external strings */
	  void *ud;  /* user data for external strings */
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
#ifndef _F2IMOD_
	enum {
	  F2Ieq,     /* no rounding; accepts only integral values */
	  F2Ifloor,  /* takes the floor of the number */
	  F2Iceil    /* takes the ceiling of the number */
	};
#endif


void luaH_getFun(void *p);

typedef struct __luaH_get
{
/* 接口函数 */
	Fun			fun;
/* 输入端口 */
	/* 输出端口 */
	lu_byte*			ret;
	/* 输入输出端口 */
	Table*			t;
	const TValue*			key;
	TValue*			res;
	/* 状态变量 */
	/* 参数变量 */
} luaH_get;

#endif // __LUAH_GET_H__