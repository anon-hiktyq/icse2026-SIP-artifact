#if !defined(__LUAH_PSETSHORTSTR_H__)
#define __LUAH_PSETSHORTSTR_H__

#include "common.h"
#include "luaH_Hgetshortstr.h"
#include "insertkey.h"
#include "retpsetcode.h"

#ifndef _cast_
#define _cast_
	#define cast ((t)(exp))
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

#ifndef _isabstkey_
#define _isabstkey_
	#define isabstkey checktag((v), LUA_VABSTKEY)
#endif

#ifndef _checknoTM_
#define _checknoTM_
	#define checknoTM ((mt) == NULL || (mt)->flags & (1u<<(e)))
#endif

#ifndef _iswhite_
#define _iswhite_
	#define iswhite testbits((x)->marked, WHITEBITS)
#endif

#ifndef _isblack_
#define _isblack_
	#define isblack testbit((x)->marked, BLACKBIT)
#endif

#ifndef _invalidateTMcache_
#define _invalidateTMcache_
	#define invalidateTMcache ((t)->flags &= cast_byte(~maskflags))
#endif

#ifndef _HOK_
#define _HOK_
	#define HOK 0
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


void luaH_psetshortstrFun(void *p);

typedef struct __luaH_psetshortstr
{
	/* Functional Interface */
	Fun			fun;
	/* Input Variables */
	/* Output Variables */
	int*			ret;
	/* In&Output Variables */
	Table*			t;
	TString*			key;
	TValue*			val;
	/* Statement Variables*/
	/* Argument Variables */
} luaH_psetshortstr;

#endif // __LUAH_PSETSHORTSTR_H__