#if !defined(__CORRECTGRAYLIST_H__)
#define __CORRECTGRAYLIST_H__

#include "common.h"
#include "getgclist.h"

#ifndef _lua_assert_
#define _lua_assert_
	#define lua_assert ((void)0)
#endif

#ifndef _LUA_VTHREAD_
#define _LUA_VTHREAD_
	#define LUA_VTHREAD makevariant(LUA_TTHREAD, 0)
#endif

#ifndef _iswhite_
#define _iswhite_
	#define iswhite testbits((x)->marked, WHITEBITS)
#endif

#ifndef _isgray_
#define _isgray_
	#define isgray (!testbits((x)->marked, WHITEBITS | bitmask(BLACKBIT)))
#endif

#ifndef _nw2black_
#define _nw2black_
	#define nw2black check_exp(!iswhite(x), l_setbit((x)->marked, BLACKBIT))
#endif

#ifndef _G_OLD_
#define _G_OLD_
	#define G_OLD 4
#endif

#ifndef _G_TOUCHED1_
#define _G_TOUCHED1_
	#define G_TOUCHED1 5
#endif

#ifndef _G_TOUCHED2_
#define _G_TOUCHED2_
	#define G_TOUCHED2 6
#endif

#ifndef _getage_
#define _getage_
	#define getage ((o)->marked & AGEBITS)
#endif

#ifndef _setage_
#define _setage_
	#define setage ((o)->marked = cast_byte(((o)->marked & (~AGEBITS)) | a))
#endif

#ifndef _isold_
#define _isold_
	#define isold (getage(o) > G_SURVIVAL)
#endif

#ifndef _lu_byte_
#define _lu_byte_
	typedef unsigned char lu_byte;
#endif

#ifndef _GCObject_
#define _GCObject_
	struct GCObject {
	  CommonHeader;
	};
#endif


void correctgraylistFun(void *p);

typedef struct __correctgraylist
{
	/* Functional Interface */
	Fun			fun;
	/* Input Variables */
	/* Output Variables */
	GCObject **			ret;
	/* In&Output Variables */
	GCObject**			p;
	/* Statement Variables*/
	/* Argument Variables */
} correctgraylist;

#endif // __CORRECTGRAYLIST_H__