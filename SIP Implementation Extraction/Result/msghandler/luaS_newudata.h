#if !defined(__LUAS_NEWUDATA_H__)
#define __LUAS_NEWUDATA_H__

#include "common.h"
#include "luaM_toobig.h"
#include "luaC_newobj.h"

#ifndef _l_unlikely_
#define _l_unlikely_
	#define l_unlikely luai_unlikely(x)
#endif

#ifndef _MAX_SIZE_
#define _MAX_SIZE_
	#define MAX_SIZE (sizeof(size_t) < sizeof(lua_Integer) ? MAX_SIZET \
				  : cast_sizet(LUA_MAXINTEGER))
#endif

#ifndef _setnilvalue_
#define _setnilvalue_
	#define setnilvalue settt_(obj, LUA_VNIL)
#endif

#ifndef _LUA_VUSERDATA_
#define _LUA_VUSERDATA_
	#define LUA_VUSERDATA makevariant(LUA_TUSERDATA, 0)
#endif

#ifndef _udatamemoffset_
#define _udatamemoffset_
	#define udatamemoffset ((nuv) == 0 ? offsetof(Udata0, bindata)  \
			   : offsetof(Udata, uv) + (sizeof(UValue) * (nuv)))
#endif

#ifndef _sizeudata_
#define _sizeudata_
	#define sizeudata (udatamemoffset(nuv) + (nb))
#endif

#ifndef _gco2u_
#define _gco2u_
	#define gco2u check_exp((o)->tt == LUA_VUSERDATA, &((cast_u(o))->u))
#endif

#ifndef _lua_State_
#define _lua_State_
	struct lua_State;
#endif

#ifndef _lu_byte_
#define _lu_byte_
	typedef unsigned char lu_byte;
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

#ifndef _UValue_
#define _UValue_
	union UValue {
	  TValue uv;
	  LUAI_MAXALIGN;  /* ensures maximum alignment for udata bytes */
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

#ifndef _lua_State_
#define _lua_State_
	struct lua_State {
	  CommonHeader;
	  lu_byte allowhook;
	  TStatus status;
	  StkIdRel top;  /* first free slot in the stack */
	  struct global_State *l_G;
	  CallInfo *ci;  /* call info for current function */
	  StkIdRel stack_last;  /* end of stack (last element + 1) */
	  StkIdRel stack;  /* stack base */
	  UpVal *openupval;  /* list of open upvalues in this stack */
	  StkIdRel tbclist;  /* list of to-be-closed variables */
	  GCObject *gclist;
	  struct lua_State *twups;  /* list of threads with open upvalues */
	  struct lua_longjmp *errorJmp;  /* current error recover point */
	  CallInfo base_ci;  /* CallInfo for first level (C host) */
	  volatile lua_Hook hook;
	  ptrdiff_t errfunc;  /* current error handling function (stack index) */
	  l_uint32 nCcalls;  /* number of nested non-yieldable or C calls */
	  int oldpc;  /* last pc traced */
	  int nci;  /* number of items in 'ci' list */
	  int basehookcount;
	  int hookcount;
	  volatile l_signalT hookmask;
	  struct {  /* info about transferred values (for call/return hooks) */
	    int ftransfer;  /* offset of first value transferred */
	    int ntransfer;  /* number of values transferred */
	  } transferinfo;
	};
#endif


void luaS_newudataFun(void *p);

typedef struct __luaS_newudata
{
	/* Functional Interface */
	Fun			fun;
	/* Input Variables */
	size_t			s;
	unsigned short			nuvalue;
	/* Output Variables */
	Udata *			ret;
	/* In&Output Variables */
	lua_State*			L;
	/* Statement Variables*/
	/* Argument Variables */
} luaS_newudata;

#endif // __LUAS_NEWUDATA_H__