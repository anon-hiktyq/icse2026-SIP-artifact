#if !defined(__CORRECTGRAYLIST_H__)
#define __CORRECTGRAYLIST_H__

#include "common.h"
#include "getgclist.h"

#ifndef _LUA_ASSERT_
	#define lua_assert ((void)0)
#endif

#ifndef _LUA_VTHREAD_
	#define LUA_VTHREAD makevariant(LUA_TTHREAD, 0)
#endif

#ifndef _ISWHITE_
	#define iswhite testbits((x)->marked, WHITEBITS)
#endif

#ifndef _ISGRAY_
	#define isgray (!testbits((x)->marked, WHITEBITS | bitmask(BLACKBIT)))
#endif

#ifndef _NW2BLACK_
	#define nw2black check_exp(!iswhite(x), l_setbit((x)->marked, BLACKBIT))
#endif

#ifndef _G_OLD_
	#define G_OLD 4
#endif

#ifndef _G_TOUCHED1_
	#define G_TOUCHED1 5
#endif

#ifndef _G_TOUCHED2_
	#define G_TOUCHED2 6
#endif

#ifndef _GETAGE_
	#define getage ((o)->marked & AGEBITS)
#endif

#ifndef _SETAGE_
	#define setage ((o)->marked = cast_byte(((o)->marked & (~AGEBITS)) | a))
#endif

#ifndef _ISOLD_
	#define isold (getage(o) > G_SURVIVAL)
#endif

#ifndef _LU_BYTE_
	typedef unsigned char lu_byte;
#endif

#ifndef _GCOBJECT_
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