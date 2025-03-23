#if !defined(__MAINPOSITIONTV_H__)
#define __MAINPOSITIONTV_H__

#include "common.h"
#include "hashint.h"
#include "luaS_hashlongstr.h"

#ifndef _ttypetag_
#define _ttypetag_
	#define ttypetag withvariant(rawtt(o))
#endif

#ifndef _LUA_VFALSE_
#define _LUA_VFALSE_
	#define LUA_VFALSE makevariant(LUA_TBOOLEAN, 0)
#endif

#ifndef _LUA_VTRUE_
#define _LUA_VTRUE_
	#define LUA_VTRUE makevariant(LUA_TBOOLEAN, 1)
#endif

#ifndef _gcvalue_
#define _gcvalue_
	#define gcvalue check_exp(iscollectable(o), val_(o).gc)
#endif

#ifndef _LUA_VNUMINT_
#define _LUA_VNUMINT_
	#define LUA_VNUMINT makevariant(LUA_TNUMBER, 0)
#endif

#ifndef _LUA_VNUMFLT_
#define _LUA_VNUMFLT_
	#define LUA_VNUMFLT makevariant(LUA_TNUMBER, 1)
#endif

#ifndef _fltvalue_
#define _fltvalue_
	#define fltvalue check_exp(ttisfloat(o), val_(o).n)
#endif

#ifndef _ivalue_
#define _ivalue_
	#define ivalue check_exp(ttisinteger(o), val_(o).i)
#endif

#ifndef _LUA_VSHRSTR_
#define _LUA_VSHRSTR_
	#define LUA_VSHRSTR makevariant(LUA_TSTRING, 0)
#endif

#ifndef _LUA_VLNGSTR_
#define _LUA_VLNGSTR_
	#define LUA_VLNGSTR makevariant(LUA_TSTRING, 1)
#endif

#ifndef _tsvalue_
#define _tsvalue_
	#define tsvalue check_exp(ttisstring(o), gco2ts(val_(o).gc))
#endif

#ifndef _LUA_VLIGHTUSERDATA_
#define _LUA_VLIGHTUSERDATA_
	#define LUA_VLIGHTUSERDATA makevariant(LUA_TLIGHTUSERDATA, 0)
#endif

#ifndef _pvalue_
#define _pvalue_
	#define pvalue check_exp(ttislightuserdata(o), val_(o).p)
#endif

#ifndef _LUA_VLCF_
#define _LUA_VLCF_
	#define LUA_VLCF makevariant(LUA_TFUNCTION, 1)
#endif

#ifndef _fvalue_
#define _fvalue_
	#define fvalue check_exp(ttislcf(o), val_(o).f)
#endif

#ifndef _hashpow2_
#define _hashpow2_
	#define hashpow2 (gnode(t, lmod((n), sizenode(t))))
#endif

#ifndef _hashmod_
#define _hashmod_
	#define hashmod (gnode(t, ((n) % ((sizenode(t)-1u)|1u))))
#endif

#ifndef _hashstr_
#define _hashstr_
	#define hashstr hashpow2(t, (str)->hash)
#endif

#ifndef _hashboolean_
#define _hashboolean_
	#define hashboolean hashpow2(t, p)
#endif

#ifndef _hashpointer_
#define _hashpointer_
	#define hashpointer hashmod(t, point2uint(p))
#endif

#ifndef _lua_Number_
#define _lua_Number_
	typedef LUA_NUMBER lua_Number;
#endif

#ifndef _lua_Integer_
#define _lua_Integer_
	typedef LUA_INTEGER lua_Integer;
#endif

#ifndef _lua_CFunction_
#define _lua_CFunction_
	typedef int (*lua_CFunction) (lua_State *L);
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

#ifndef _TString_
#define _TString_
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


void mainpositionTVFun(void *p);

typedef struct __mainpositionTV
{
	/* Functional Interface */
	Fun			fun;
	/* Input Variables */
	/* Output Variables */
	Node *			ret;
	/* In&Output Variables */
	const Table*			t;
	const TValue*			key;
	/* Statement Variables*/
	/* Argument Variables */
} mainpositionTV;

#endif // __MAINPOSITIONTV_H__