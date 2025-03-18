#if !defined(__PSETINT_H__)
#define __PSETINT_H__

#include "common.h"


#ifndef _LUAH_FASTSETI_
	#define luaH_fastseti { Table *h = t; lua_Unsigned u = l_castS2U(k) - 1u; \
	    if ((u < h->asize)) { \
	      lu_byte *tag = getArrTag(h, u); \
	      if (checknoTM(h->metatable, TM_NEWINDEX) || !tagisempty(*tag)) \
	        { fval2arr(h, u, tag, val); hres = HOK; } \
	      else hres = ~cast_int(u); } \
	    else { hres = luaH_psetint(h, k, val); }}
#endif

#ifndef _LUA_INTEGER_
	typedef LUA_INTEGER lua_Integer;
#endif

#ifndef _LUA_UNSIGNED_
	typedef LUA_UNSIGNED lua_Unsigned;
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

void psetintFun(void *p);

typedef struct __psetint
{
	/* Functional Interface */
	Fun			fun;
	/* Input Variables */
	lua_Integer			key;
	/* Output Variables */
	int			hres;
	int*			ret;
	/* In&Output Variables */
	Table*			t;
	TValue*			val;
	/* Statement Variables*/
	/* Argument Variables */
} psetint;

#endif // __PSETINT_H__