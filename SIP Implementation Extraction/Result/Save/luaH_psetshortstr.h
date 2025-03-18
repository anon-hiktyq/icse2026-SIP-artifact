#if !defined(__LUAH_PSETSHORTSTR_H__)
#define __LUAH_PSETSHORTSTR_H__

#include "common.h"
#include "luaH_Hgetshortstr.h"
#include "insertkey.h"
#include "retpsetcode.h"

#ifndef _CAST_
	#define cast ((t)(exp))
#endif

#ifndef _SETOBJ_
	#define setobj { TValue *io1=(obj1); const TValue *io2=(obj2); \
	          io1->value_ = io2->value_; settt_(io1, io2->tt_); \
		  checkliveness(L,io1); lua_assert(!isnonstrictnil(io1)); }
#endif

#ifndef _TTISNIL_
	#define ttisnil checktype((v), LUA_TNIL)
#endif

#ifndef _ISABSTKEY_
	#define isabstkey checktag((v), LUA_VABSTKEY)
#endif

#ifndef _CHECKNOTM_
	#define checknoTM ((mt) == NULL || (mt)->flags & (1u<<(e)))
#endif

#ifndef _ISWHITE_
	#define iswhite testbits((x)->marked, WHITEBITS)
#endif

#ifndef _ISBLACK_
	#define isblack testbit((x)->marked, BLACKBIT)
#endif

#ifndef _INVALIDATETMCACHE_
	#define invalidateTMcache ((t)->flags &= cast_byte(~maskflags))
#endif

#ifndef _HOK_
	#define HOK 0
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