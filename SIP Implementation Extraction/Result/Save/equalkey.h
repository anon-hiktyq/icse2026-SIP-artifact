#if !defined(__EQUALKEY_H__)
#define __EQUALKEY_H__

#include "common.h"
#include "luaS_eqlngstr.h"

#ifndef _LUAI_NUMEQ_
	#define luai_numeq ((a)==(b))
#endif

#ifndef _RAWTT_
	#define rawtt ((o)->tt_)
#endif

#ifndef _LUA_VNIL_
	#define LUA_VNIL makevariant(LUA_TNIL, 0)
#endif

#ifndef _LUA_VFALSE_
	#define LUA_VFALSE makevariant(LUA_TBOOLEAN, 0)
#endif

#ifndef _LUA_VTRUE_
	#define LUA_VTRUE makevariant(LUA_TBOOLEAN, 1)
#endif

#ifndef _ISCOLLECTABLE_
	#define iscollectable (rawtt(o) & BIT_ISCOLLECTABLE)
#endif

#ifndef _CTB_
	#define ctb ((t) | BIT_ISCOLLECTABLE)
#endif

#ifndef _GCVALUE_
	#define gcvalue check_exp(iscollectable(o), val_(o).gc)
#endif

#ifndef _GCVALUERAW_
	#define gcvalueraw ((v).gc)
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

#ifndef _FLTVALUERAW_
	#define fltvalueraw ((v).n)
#endif

#ifndef _LUA_VLNGSTR_
	#define LUA_VLNGSTR makevariant(LUA_TSTRING, 1)
#endif

#ifndef _TSVALUE_
	#define tsvalue check_exp(ttisstring(o), gco2ts(val_(o).gc))
#endif

#ifndef _LUA_VLIGHTUSERDATA_
	#define LUA_VLIGHTUSERDATA makevariant(LUA_TLIGHTUSERDATA, 0)
#endif

#ifndef _PVALUE_
	#define pvalue check_exp(ttislightuserdata(o), val_(o).p)
#endif

#ifndef _PVALUERAW_
	#define pvalueraw ((v).p)
#endif

#ifndef _LUA_VLCF_
	#define LUA_VLCF makevariant(LUA_TFUNCTION, 1)
#endif

#ifndef _FVALUE_
	#define fvalue check_exp(ttislcf(o), val_(o).f)
#endif

#ifndef _FVALUERAW_
	#define fvalueraw ((v).f)
#endif

#ifndef _KEYTT_
	#define keytt ((node)->u.key_tt)
#endif

#ifndef _KEYVAL_
	#define keyval ((node)->u.key_val)
#endif

#ifndef _KEYIVAL_
	#define keyival (keyval(node).i)
#endif

#ifndef _KEYSTRVAL_
	#define keystrval (gco2ts(keyval(node).gc))
#endif

#ifndef _KEYISDEAD_
	#define keyisdead (keytt(node) == LUA_TDEADKEY)
#endif

#ifndef _LUA_NUMBER_
	typedef LUA_NUMBER lua_Number;
#endif

#ifndef _LUA_INTEGER_
	typedef LUA_INTEGER lua_Integer;
#endif

#ifndef _LUA_CFUNCTION_
	typedef int (*lua_CFunction) (lua_State *L);
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

#ifndef _NODE_
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