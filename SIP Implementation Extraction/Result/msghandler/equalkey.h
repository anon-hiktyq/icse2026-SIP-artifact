#if !defined(__EQUALKEY_H__)
#define __EQUALKEY_H__

#include "common.h"
#include "luaS_eqlngstr.h"

#ifndef _luai_numeq_
#define _luai_numeq_
	#define luai_numeq ((a)==(b))
#endif

#ifndef _rawtt_
#define _rawtt_
	#define rawtt ((o)->tt_)
#endif

#ifndef _LUA_VNIL_
#define _LUA_VNIL_
	#define LUA_VNIL makevariant(LUA_TNIL, 0)
#endif

#ifndef _LUA_VFALSE_
#define _LUA_VFALSE_
	#define LUA_VFALSE makevariant(LUA_TBOOLEAN, 0)
#endif

#ifndef _LUA_VTRUE_
#define _LUA_VTRUE_
	#define LUA_VTRUE makevariant(LUA_TBOOLEAN, 1)
#endif

#ifndef _iscollectable_
#define _iscollectable_
	#define iscollectable (rawtt(o) & BIT_ISCOLLECTABLE)
#endif

#ifndef _ctb_
#define _ctb_
	#define ctb ((t) | BIT_ISCOLLECTABLE)
#endif

#ifndef _gcvalue_
#define _gcvalue_
	#define gcvalue check_exp(iscollectable(o), val_(o).gc)
#endif

#ifndef _gcvalueraw_
#define _gcvalueraw_
	#define gcvalueraw ((v).gc)
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

#ifndef _fltvalueraw_
#define _fltvalueraw_
	#define fltvalueraw ((v).n)
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

#ifndef _pvalueraw_
#define _pvalueraw_
	#define pvalueraw ((v).p)
#endif

#ifndef _LUA_VLCF_
#define _LUA_VLCF_
	#define LUA_VLCF makevariant(LUA_TFUNCTION, 1)
#endif

#ifndef _fvalue_
#define _fvalue_
	#define fvalue check_exp(ttislcf(o), val_(o).f)
#endif

#ifndef _fvalueraw_
#define _fvalueraw_
	#define fvalueraw ((v).f)
#endif

#ifndef _keytt_
#define _keytt_
	#define keytt ((node)->u.key_tt)
#endif

#ifndef _keyval_
#define _keyval_
	#define keyval ((node)->u.key_val)
#endif

#ifndef _keyival_
#define _keyival_
	#define keyival (keyval(node).i)
#endif

#ifndef _keystrval_
#define _keystrval_
	#define keystrval (gco2ts(keyval(node).gc))
#endif

#ifndef _keyisdead_
#define _keyisdead_
	#define keyisdead (keytt(node) == LUA_TDEADKEY)
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


void equalkeyFun(void *p);

typedef struct __equalkey
{
	/* Functional Interface */
	Fun			fun;
	/* Input Variables */
	const TValue*			k1;
	const Node*			n2;
	int			deadok;
	/* Output Variables */
	int*			ret;
	/* In&Output Variables */
	/* Statement Variables*/
	/* Argument Variables */
} equalkey;

#endif // __EQUALKEY_H__