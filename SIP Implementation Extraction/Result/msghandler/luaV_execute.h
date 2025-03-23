#if !defined(__LUAV_EXECUTE_H__)
#define __LUAV_EXECUTE_H__

#include "common.h"
#include "luaG_tracecall.h"
#include "luaG_traceexec.h"
#include "luaV_finishget.h"
#include "luaH_get.h"
#include "luaC_barrierback_.h"
#include "luaH_pset.h"
#include "luaV_finishset.h"
#include "luaH_new.h"
#include "luaH_resize.h"
#include "luaV_modf.h"
#include "luaV_shiftl.h"
#include "luaV_tointegerns.h"
#include "luaT_trybinTM.h"
#include "luaC_step.h"
#include "lessthanothers.h"
#include "lessequalothers.h"
#include "luaD_precall.h"
#include "luaF_closeupval.h"
#include "luaD_pretailcall.h"
#include "luaD_poscall.h"
#include "luaF_close.h"
#include "floatforloop.h"
#include "forprep.h"
#include "luaD_call.h"
#include "luaH_resizearray.h"
#include "luaD_hookcall.h"

#ifndef _l_unlikely_
#define _l_unlikely_
	#define l_unlikely luai_unlikely(x)
#endif

#ifndef _LUA_OK_
#define _LUA_OK_
	#define LUA_OK 0
#endif

#ifndef _lua_assert_
#define _lua_assert_
	#define lua_assert ((void)0)
#endif

#ifndef _cast_void_
#define _cast_void_
	#define cast_void cast(void, (i))
#endif

#ifndef _cast_num_
#define _cast_num_
	#define cast_num cast(lua_Number, (i))
#endif

#ifndef _cast_int_
#define _cast_int_
	#define cast_int cast(int, (i))
#endif

#ifndef _cast_uint_
#define _cast_uint_
	#define cast_uint cast(unsigned int, (i))
#endif

#ifndef _l_castS2U_
#define _l_castS2U_
	#define l_castS2U ((lua_Unsigned)(i))
#endif

#ifndef _l_castU2S_
#define _l_castU2S_
	#define l_castU2S ((lua_Integer)(i))
#endif

#ifndef _luai_numidiv_
#define _luai_numidiv_
	#define luai_numidiv ((void)L, l_floor(luai_numdiv(L,a,b)))
#endif

#ifndef _luai_numdiv_
#define _luai_numdiv_
	#define luai_numdiv ((a)/(b))
#endif

#ifndef _luai_numpow_
#define _luai_numpow_
	#define luai_numpow ((void)L, (b == 2) ? (a)*(a) : l_mathop(pow)(a,b))
#endif

#ifndef _luai_numadd_
#define _luai_numadd_
	#define luai_numadd ((a)+(b))
#endif

#ifndef _luai_numsub_
#define _luai_numsub_
	#define luai_numsub ((a)-(b))
#endif

#ifndef _luai_nummul_
#define _luai_nummul_
	#define luai_nummul ((a)*(b))
#endif

#ifndef _luai_numunm_
#define _luai_numunm_
	#define luai_numunm (-(a))
#endif

#ifndef _luai_numeq_
#define _luai_numeq_
	#define luai_numeq ((a)==(b))
#endif

#ifndef _luai_numlt_
#define _luai_numlt_
	#define luai_numlt ((a)<(b))
#endif

#ifndef _luai_numle_
#define _luai_numle_
	#define luai_numle ((a)<=(b))
#endif

#ifndef _luai_numgt_
#define _luai_numgt_
	#define luai_numgt ((a)>(b))
#endif

#ifndef _luai_numge_
#define _luai_numge_
	#define luai_numge ((a)>=(b))
#endif

#ifndef _setobj_
#define _setobj_
	#define setobj { TValue *io1=(obj1); const TValue *io2=(obj2); \
	          io1->value_ = io2->value_; settt_(io1, io2->tt_); \
		  checkliveness(L,io1); lua_assert(!isnonstrictnil(io1)); }
#endif

#ifndef _setobjs2s_
#define _setobjs2s_
	#define setobjs2s setobj(L,s2v(o1),s2v(o2))
#endif

#ifndef _setobj2s_
#define _setobj2s_
	#define setobj2s setobj(L,s2v(o1),o2)
#endif

#ifndef _s2v_
#define _s2v_
	#define s2v (&(o)->val)
#endif

#ifndef _ttisnil_
#define _ttisnil_
	#define ttisnil checktype((v), LUA_TNIL)
#endif

#ifndef _tagisempty_
#define _tagisempty_
	#define tagisempty (novariant(tag) == LUA_TNIL)
#endif

#ifndef _setnilvalue_
#define _setnilvalue_
	#define setnilvalue settt_(obj, LUA_VNIL)
#endif

#ifndef _l_isfalse_
#define _l_isfalse_
	#define l_isfalse (ttisfalse(o) || ttisnil(o))
#endif

#ifndef _setbfvalue_
#define _setbfvalue_
	#define setbfvalue settt_(obj, LUA_VFALSE)
#endif

#ifndef _setbtvalue_
#define _setbtvalue_
	#define setbtvalue settt_(obj, LUA_VTRUE)
#endif

#ifndef _ttisfloat_
#define _ttisfloat_
	#define ttisfloat checktag((o), LUA_VNUMFLT)
#endif

#ifndef _ttisinteger_
#define _ttisinteger_
	#define ttisinteger checktag((o), LUA_VNUMINT)
#endif

#ifndef _fltvalue_
#define _fltvalue_
	#define fltvalue check_exp(ttisfloat(o), val_(o).n)
#endif

#ifndef _ivalue_
#define _ivalue_
	#define ivalue check_exp(ttisinteger(o), val_(o).i)
#endif

#ifndef _setfltvalue_
#define _setfltvalue_
	#define setfltvalue { TValue *io=(obj); val_(io).n=(x); settt_(io, LUA_VNUMFLT); }
#endif

#ifndef _setivalue_
#define _setivalue_
	#define setivalue { TValue *io=(obj); val_(io).i=(x); settt_(io, LUA_VNUMINT); }
#endif

#ifndef _chgivalue_
#define _chgivalue_
	#define chgivalue { TValue *io=(obj); lua_assert(ttisinteger(io)); val_(io).i=(x); }
#endif

#ifndef _tsvalue_
#define _tsvalue_
	#define tsvalue check_exp(ttisstring(o), gco2ts(val_(o).gc))
#endif

#ifndef _hvalue_
#define _hvalue_
	#define hvalue check_exp(ttistable(o), gco2t(val_(o).gc))
#endif

#ifndef _sethvalue2s_
#define _sethvalue2s_
	#define sethvalue2s sethvalue(L,s2v(o),h)
#endif

#ifndef _CIST_FRESH_
#define _CIST_FRESH_
	#define CIST_FRESH cast(l_uint32, CIST_C << 1)
#endif

#ifndef _get_nresults_
#define _get_nresults_
	#define get_nresults (cast_int((cs) & CIST_NRESULTS) - 1)
#endif

#ifndef _obj2gco_
#define _obj2gco_
	#define obj2gco check_exp((v)->tt >= LUA_TSTRING, &(cast_u(v)->gc))
#endif

#ifndef _pcRel_
#define _pcRel_
	#define pcRel (cast_int((pc) - (p)->code) - 1)
#endif

#ifndef _ci_func_
#define _ci_func_
	#define ci_func (clLvalue(s2v((ci)->func.p)))
#endif

#ifndef _CLOSEKTOP_
#define _CLOSEKTOP_
	#define CLOSEKTOP (LUA_ERRERR + 1)
#endif

#ifndef _luaC_barrier_
#define _luaC_barrier_
	#define luaC_barrier (  \
		iscollectable(v) ? luaC_objbarrier(L,p,gcvalue(v)) : cast_void(0))
#endif

#ifndef _luaC_barrierback_
#define _luaC_barrierback_
	#define luaC_barrierback (  \
		iscollectable(v) ? luaC_objbarrierback(L, p, gcvalue(v)) : cast_void(0))
#endif

#ifndef _MAXARG_vC_
#define _MAXARG_vC_
	#define MAXARG_vC ((1<<SIZE_vC)-1)
#endif

#ifndef _GET_OPCODE_
#define _GET_OPCODE_
	#define GET_OPCODE (cast(OpCode, ((i)>>POS_OP) & MASK1(SIZE_OP,0)))
#endif

#ifndef _GETARG_A_
#define _GETARG_A_
	#define GETARG_A getarg(i, POS_A, SIZE_A)
#endif

#ifndef _GETARG_B_
#define _GETARG_B_
	#define GETARG_B check_exp(checkopm(i, iABC), getarg(i, POS_B, SIZE_B))
#endif

#ifndef _GETARG_vB_
#define _GETARG_vB_
	#define GETARG_vB check_exp(checkopm(i, ivABC), getarg(i, POS_vB, SIZE_vB))
#endif

#ifndef _GETARG_sB_
#define _GETARG_sB_
	#define GETARG_sB sC2int(GETARG_B(i))
#endif

#ifndef _GETARG_C_
#define _GETARG_C_
	#define GETARG_C check_exp(checkopm(i, iABC), getarg(i, POS_C, SIZE_C))
#endif

#ifndef _GETARG_vC_
#define _GETARG_vC_
	#define GETARG_vC check_exp(checkopm(i, ivABC), getarg(i, POS_vC, SIZE_vC))
#endif

#ifndef _GETARG_sC_
#define _GETARG_sC_
	#define GETARG_sC sC2int(GETARG_C(i))
#endif

#ifndef _TESTARG_k_
#define _TESTARG_k_
	#define TESTARG_k (cast_int(((i) & (1u << POS_k))))
#endif

#ifndef _GETARG_k_
#define _GETARG_k_
	#define GETARG_k getarg(i, POS_k, 1)
#endif

#ifndef _GETARG_Bx_
#define _GETARG_Bx_
	#define GETARG_Bx check_exp(checkopm(i, iABx), getarg(i, POS_Bx, SIZE_Bx))
#endif

#ifndef _GETARG_Ax_
#define _GETARG_Ax_
	#define GETARG_Ax check_exp(checkopm(i, iAx), getarg(i, POS_Ax, SIZE_Ax))
#endif

#ifndef _GETARG_sBx_
#define _GETARG_sBx_
	#define GETARG_sBx check_exp(checkopm(i, iAsBx), getarg(i, POS_Bx, SIZE_Bx) - OFFSET_sBx)
#endif

#ifndef _HOK_
#define _HOK_
	#define HOK 0
#endif

#ifndef _obj2arr_
#define _obj2arr_
	#define obj2arr (*getArrTag(h,(k)) = (val)->tt_, *getArrVal(h,(k)) = (val)->value_)
#endif

#ifndef _tonumberns_
#define _tonumberns_
	#define tonumberns (ttisfloat(o) ? ((n) = fltvalue(o), 1) : \
		(ttisinteger(o) ? ((n) = cast_num(ivalue(o)), 1) : 0))
#endif

#ifndef _tointegerns_
#define _tointegerns_
	#define tointegerns (l_likely(ttisinteger(o)) ? (*(i) = ivalue(o), 1) \
	                          : luaV_tointegerns(o,i,LUA_FLOORN2I))
#endif

#ifndef _intop_
#define _intop_
	#define intop l_castU2S(l_castS2U(v1) op l_castS2U(v2))
#endif

#ifndef _luaV_rawequalobj_
#define _luaV_rawequalobj_
	#define luaV_rawequalobj luaV_equalobj(NULL,t1,t2)
#endif

#ifndef _luaV_fastget_
#define _luaV_fastget_
	#define luaV_fastget (tag = (!ttistable(t) ? LUA_VNOTABLE : f(hvalue(t), k, res)))
#endif

#ifndef _luaV_fastgeti_
#define _luaV_fastgeti_
	#define luaV_fastgeti if (!ttistable(t)) tag = LUA_VNOTABLE; \
	  else { luaH_fastgeti(hvalue(t), k, res, tag); }
#endif

#ifndef _luaV_fastset_
#define _luaV_fastset_
	#define luaV_fastset (hres = (!ttistable(t) ? HNOTATABLE : f(hvalue(t), k, val)))
#endif

#ifndef _luaV_fastseti_
#define _luaV_fastseti_
	#define luaV_fastseti if (!ttistable(t)) hres = HNOTATABLE; \
	  else { luaH_fastseti(hvalue(t), k, val, hres); }
#endif

#ifndef _luaV_finishfastset_
#define _luaV_finishfastset_
	#define luaV_finishfastset luaC_barrierback(L, gcvalue(t), v)
#endif

#ifndef _luaV_shiftr_
#define _luaV_shiftr_
	#define luaV_shiftr luaV_shiftl(x,intop(-, 0, y))
#endif

#ifndef _LUA_USE_JUMPTABLE_
#define _LUA_USE_JUMPTABLE_
	#define LUA_USE_JUMPTABLE 0
#endif

#ifndef _l_addi_
#define _l_addi_
	#define l_addi intop(+, a, b)
#endif

#ifndef _l_subi_
#define _l_subi_
	#define l_subi intop(-, a, b)
#endif

#ifndef _l_muli_
#define _l_muli_
	#define l_muli intop(*, a, b)
#endif

#ifndef _l_band_
#define _l_band_
	#define l_band intop(&, a, b)
#endif

#ifndef _l_bor_
#define _l_bor_
	#define l_bor intop(|, a, b)
#endif

#ifndef _l_bxor_
#define _l_bxor_
	#define l_bxor intop(^, a, b)
#endif

#ifndef _l_lti_
#define _l_lti_
	#define l_lti (a < b)
#endif

#ifndef _l_lei_
#define _l_lei_
	#define l_lei (a <= b)
#endif

#ifndef _l_gti_
#define _l_gti_
	#define l_gti (a > b)
#endif

#ifndef _l_gei_
#define _l_gei_
	#define l_gei (a >= b)
#endif

#ifndef _op_arithI_
#define _op_arithI_
	#define op_arithI {  \
	  StkId ra = RA(i); \
	  TValue *v1 = vRB(i);  \
	  int imm = GETARG_sC(i);  \
	  if (ttisinteger(v1)) {  \
	    lua_Integer iv1 = ivalue(v1);  \
	    pc++; setivalue(s2v(ra), iop(L, iv1, imm));  \
	  }  \
	  else if (ttisfloat(v1)) {  \
	    lua_Number nb = fltvalue(v1);  \
	    lua_Number fimm = cast_num(imm);  \
	    pc++; setfltvalue(s2v(ra), fop(L, nb, fimm)); \
	  }}
#endif

#ifndef _op_arithf_
#define _op_arithf_
	#define op_arithf {  \
	  StkId ra = RA(i); \
	  TValue *v1 = vRB(i);  \
	  TValue *v2 = vRC(i);  \
	  op_arithf_aux(L, v1, v2, fop); }
#endif

#ifndef _op_arithfK_
#define _op_arithfK_
	#define op_arithfK {  \
	  StkId ra = RA(i); \
	  TValue *v1 = vRB(i);  \
	  TValue *v2 = KC(i); lua_assert(ttisnumber(v2));  \
	  op_arithf_aux(L, v1, v2, fop); }
#endif

#ifndef _op_arith_
#define _op_arith_
	#define op_arith {  \
	  TValue *v1 = vRB(i);  \
	  TValue *v2 = vRC(i);  \
	  op_arith_aux(L, v1, v2, iop, fop); }
#endif

#ifndef _op_arithK_
#define _op_arithK_
	#define op_arithK {  \
	  TValue *v1 = vRB(i);  \
	  TValue *v2 = KC(i); lua_assert(ttisnumber(v2));  \
	  op_arith_aux(L, v1, v2, iop, fop); }
#endif

#ifndef _op_bitwiseK_
#define _op_bitwiseK_
	#define op_bitwiseK {  \
	  StkId ra = RA(i); \
	  TValue *v1 = vRB(i);  \
	  TValue *v2 = KC(i);  \
	  lua_Integer i1;  \
	  lua_Integer i2 = ivalue(v2);  \
	  if (tointegerns(v1, &i1)) {  \
	    pc++; setivalue(s2v(ra), op(i1, i2));  \
	  }}
#endif

#ifndef _op_bitwise_
#define _op_bitwise_
	#define op_bitwise {  \
	  StkId ra = RA(i); \
	  TValue *v1 = vRB(i);  \
	  TValue *v2 = vRC(i);  \
	  lua_Integer i1; lua_Integer i2;  \
	  if (tointegerns(v1, &i1) && tointegerns(v2, &i2)) {  \
	    pc++; setivalue(s2v(ra), op(i1, i2));  \
	  }}
#endif

#ifndef _op_order_
#define _op_order_
	#define op_order {  \
	  StkId ra = RA(i); \
	  int cond;  \
	  TValue *rb = vRB(i);  \
	  if (ttisinteger(s2v(ra)) && ttisinteger(rb)) {  \
	    lua_Integer ia = ivalue(s2v(ra));  \
	    lua_Integer ib = ivalue(rb);  \
	    cond = opi(ia, ib);  \
	  }  \
	  else if (ttisnumber(s2v(ra)) && ttisnumber(rb))  \
	    cond = opn(s2v(ra), rb);  \
	  else  \
	    Protect(cond = other(L, s2v(ra), rb));  \
	  docondjump(); }
#endif

#ifndef _op_orderI_
#define _op_orderI_
	#define op_orderI {  \
	  StkId ra = RA(i); \
	  int cond;  \
	  int im = GETARG_sB(i);  \
	  if (ttisinteger(s2v(ra)))  \
	    cond = opi(ivalue(s2v(ra)), im);  \
	  else if (ttisfloat(s2v(ra))) {  \
	    lua_Number fa = fltvalue(s2v(ra));  \
	    lua_Number fim = cast_num(im);  \
	    cond = opf(fa, fim);  \
	  }  \
	  else {  \
	    int isf = GETARG_C(i);  \
	    Protect(cond = luaT_callorderiTM(L, s2v(ra), im, inv, isf, tm));  \
	  }  \
	  docondjump(); }
#endif

#ifndef _RA_
#define _RA_
	#define RA (base+GETARG_A(i))
#endif

#ifndef _RB_
#define _RB_
	#define RB (base+GETARG_B(i))
#endif

#ifndef _vRB_
#define _vRB_
	#define vRB s2v(RB(i))
#endif

#ifndef _KB_
#define _KB_
	#define KB (k+GETARG_B(i))
#endif

#ifndef _vRC_
#define _vRC_
	#define vRC s2v(RC(i))
#endif

#ifndef _KC_
#define _KC_
	#define KC (k+GETARG_C(i))
#endif

#ifndef _RKC_
#define _RKC_
	#define RKC ((TESTARG_k(i)) ? k + GETARG_C(i) : s2v(base + GETARG_C(i)))
#endif

#ifndef _updatetrap_
#define _updatetrap_
	#define updatetrap (trap = ci->u.l.trap)
#endif

#ifndef _updatebase_
#define _updatebase_
	#define updatebase (base = ci->func.p + 1)
#endif

#ifndef _updatestack_
#define _updatestack_
	#define updatestack { if (l_unlikely(trap)) { updatebase(ci); ra = RA(i); } }
#endif

#ifndef _dojump_
#define _dojump_
	#define dojump { pc += GETARG_sJ(i) + e; updatetrap(ci); }
#endif

#ifndef _donextjump_
#define _donextjump_
	#define donextjump { Instruction ni = *pc; dojump(ci, ni, 1); }
#endif

#ifndef _docondjump_
#define _docondjump_
	#define docondjump if (cond != GETARG_k(i)) pc++; else donextjump(ci);
#endif

#ifndef _savepc_
#define _savepc_
	#define savepc (ci->u.l.savedpc = pc)
#endif

#ifndef _savestate_
#define _savestate_
	#define savestate (savepc(L), L->top.p = ci->top.p)
#endif

#ifndef _Protect_
#define _Protect_
	#define Protect (savestate(L,ci), (exp), updatetrap(ci))
#endif

#ifndef _ProtectNT_
#define _ProtectNT_
	#define ProtectNT (savepc(L), (exp), updatetrap(ci))
#endif

#ifndef _halfProtect_
#define _halfProtect_
	#define halfProtect (savestate(L,ci), (exp))
#endif

#ifndef _checkGC_
#define _checkGC_
	#define checkGC { luaC_condGC(L, (savepc(L), L->top.p = (c)), \
	                         updatetrap(ci)); \
	           luai_threadyield(L); }
#endif

#ifndef _vmfetch_
#define _vmfetch_
	#define vmfetch { \
	  if (l_unlikely(trap)) {
#endif

#ifndef _vmbreak_
#define _vmbreak_
	#define vmbreak break
#endif

#ifndef _vmbreak_
#define _vmbreak_
	#define vmbreak break
#endif

#ifndef _lua_State_
#define _lua_State_
	struct lua_State;
#endif

#ifndef _lua_Number_
#define _lua_Number_
	typedef LUA_NUMBER lua_Number;
#endif

#ifndef _lua_Integer_
#define _lua_Integer_
	typedef LUA_INTEGER lua_Integer;
#endif

#ifndef _lua_Unsigned_
#define _lua_Unsigned_
	typedef LUA_UNSIGNED lua_Unsigned;
#endif

#ifndef _l_mem_
#define _l_mem_
	typedef ptrdiff_t l_mem;
#endif

#ifndef _lu_byte_
#define _lu_byte_
	typedef unsigned char lu_byte;
#endif

#ifndef _TStatus_
#define _TStatus_
	typedef lu_byte TStatus;
#endif

#ifndef _l_uint32_
#define _l_uint32_
	typedef unsigned int l_uint32;
#endif

#ifndef _CallInfo_
#define _CallInfo_
	typedef struct CallInfo CallInfo;
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

#ifndef _StkId_
#define _StkId_
	typedef StackValue *StkId;
#endif

#ifndef _StkIdRel_
#define _StkIdRel_
	union {
	  StkId p;  /* actual pointer */
	  ptrdiff_t offset;  /* used while the stack is being reallocated */
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

#ifndef _Inion_
#define _Inion_
	typedef l_uint32 Instruction;
#endif

#ifndef _Proto_
#define _Proto_
	struct Proto {
	  CommonHeader;
	  lu_byte numparams;  /* number of fixed (named) parameters */
	  lu_byte flag;
	  lu_byte maxstacksize;  /* number of registers needed by this function */
	  int sizeupvalues;  /* size of 'upvalues' */
	  int sizek;  /* size of 'k' */
	  int sizecode;
	  int sizelineinfo;
	  int sizep;  /* size of 'p' */
	  int sizelocvars;
	  int sizeabslineinfo;  /* size of 'abslineinfo' */
	  int linedefined;  /* debug information  */
	  int lastlinedefined;  /* debug information  */
	  TValue *k;  /* constants used by the function */
	  Instruction *code;  /* opcodes */
	  struct Proto **p;  /* functions defined inside the function */
	  Upvaldesc *upvalues;  /* upvalue information */
	  ls_byte *lineinfo;  /* information about source lines (debug information) */
	  AbsLineInfo *abslineinfo;  /* idem */
	  LocVar *locvars;  /* information about local variables (debug information) */
	  TString  *source;  /* used for debug information */
	  GCObject *gclist;
	};
#endif

#ifndef _UpVal_
#define _UpVal_
	struct UpVal {
	  CommonHeader;
	  union {
	    TValue *p;  /* points to stack or to its own value */
	    ptrdiff_t offset;  /* used while the stack is being reallocated */
	  } v;
	  union {
	    struct {  /* (when open) */
	      struct UpVal *next;  /* linked list */
	      struct UpVal **previous;
	    } open;
	    TValue value;  /* the value (when closed) */
	  } u;
	};
#endif

#ifndef _LClosure_
#define _LClosure_
	struct LClosure {
	  ClosureHeader;
	  struct Proto *p;
	  UpVal *upvals[1];  /* list of upvalues */
	};
#endif

#ifndef _Closure_
#define _Closure_
	union Closure {
	  CClosure c;
	  LClosure l;
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

#ifndef _TMS_
#define _TMS_
	enum {
	  TM_INDEX,
	  TM_NEWINDEX,
	  TM_GC,
	  TM_MODE,
	  TM_LEN,
	  TM_EQ,  /* last tag method with fast access */
	  TM_ADD,
	  TM_SUB,
	  TM_MUL,
	  TM_MOD,
	  TM_POW,
	  TM_DIV,
	  TM_IDIV,
	  TM_BAND,
	  TM_BOR,
	  TM_BXOR,
	  TM_SHL,
	  TM_SHR,
	  TM_UNM,
	  TM_BNOT,
	  TM_LT,
	  TM_LE,
	  TM_CONCAT,
	  TM_CALL,
	  TM_CLOSE,
	  TM_N		/* number of elements in the enum */
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

#ifndef _global_State_
#define _global_State_
	struct global_State {
	  lua_Alloc frealloc;  /* function to reallocate memory */
	  void *ud;         /* auxiliary data to 'frealloc' */
	  l_mem GCtotalbytes;  /* number of bytes currently allocated + debt */
	  l_mem GCdebt;  /* bytes counted but not yet allocated */
	  l_mem GCmarked;  /* number of objects marked in a GC cycle */
	  l_mem GCmajorminor;  /* auxiliary counter to control major-minor shifts */
	  stringtable strt;  /* hash table for strings */
	  TValue l_registry;
	  TValue nilvalue;  /* a nil value */
	  unsigned int seed;  /* randomized seed for hashes */
	  lu_byte gcparams[LUA_GCPN];
	  lu_byte currentwhite;
	  lu_byte gcstate;  /* state of garbage collector */
	  lu_byte gckind;  /* kind of GC running */
	  lu_byte gcstopem;  /* stops emergency collections */
	  lu_byte gcstp;  /* control whether GC is running */
	  lu_byte gcemergency;  /* true if this is an emergency collection */
	  GCObject *allgc;  /* list of all collectable objects */
	  GCObject **sweepgc;  /* current position of sweep in list */
	  GCObject *finobj;  /* list of collectable objects with finalizers */
	  GCObject *gray;  /* list of gray objects */
	  GCObject *grayagain;  /* list of objects to be traversed atomically */
	  GCObject *weak;  /* list of tables with weak values */
	  GCObject *ephemeron;  /* list of ephemeron tables (weak keys) */
	  GCObject *allweak;  /* list of all-weak tables */
	  GCObject *tobefnz;  /* list of userdata to be GC */
	  GCObject *fixedgc;  /* list of objects not to be collected */
	  /* fields for generational collector */
	  GCObject *survival;  /* start of objects that survived one GC cycle */
	  GCObject *old1;  /* start of old1 objects */
	  GCObject *reallyold;  /* objects more than one cycle old ("really old") */
	  GCObject *firstold1;  /* first OLD1 object in the list (if any) */
	  GCObject *finobjsur;  /* list of survival objects with finalizers */
	  GCObject *finobjold1;  /* list of old1 objects with finalizers */
	  GCObject *finobjrold;  /* list of really old objects with finalizers */
	  struct lua_State *twups;  /* list of threads with open upvalues */
	  lua_CFunction panic;  /* to be called in unprotected errors */
	  TString *memerrmsg;  /* message for memory-allocation errors */
	  TString *tmname[TM_N];  /* array with tag-method names */
	  struct Table *mt[LUA_NUMTYPES];  /* metatables for basic types */
	  TString *strcache[STRCACHE_N][STRCACHE_M];  /* cache for strings in API */
	  lua_WarnFunction warnf;  /* warning function */
	  void *ud_warn;         /* auxiliary data to 'warnf' */
	  LX mainth;  /* main thread of this state */
	};
#endif

#ifndef _F2Imod_
#define _F2Imod_
	enum {
	  F2Ieq,     /* no rounding; accepts only integral values */
	  F2Ifloor,  /* takes the floor of the number */
	  F2Iceil    /* takes the ceiling of the number */
	};
#endif


void luaV_executeFun(void *p);

typedef struct __luaV_execute
{
	/* Functional Interface */
	Fun			fun;
	/* Input Variables */
	/* Output Variables */
	/* In&Output Variables */
	lua_State*			L;
	CallInfo*			ci;
	/* Statement Variables*/
	/* Argument Variables */
} luaV_execute;

#endif // __LUAV_EXECUTE_H__