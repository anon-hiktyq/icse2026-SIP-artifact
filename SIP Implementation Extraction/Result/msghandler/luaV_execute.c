#include "luaV_execute.h"
void luaV_executeFun(void *p) 
{
    luaV_execute *pIp = (luaV_execute*)p;
  LClosure *cl;
  TValue *k;
  StkId base;
  const Instruction *pc;
  int trap;
#if LUA_USE_JUMPTABLE
#include "ljumptab.h"
#endif
 startfunc:
  trap = (pIp->L)->hookmask;
 returning:  /* trap already set */
  {cl = ci_func(pIp->ci);}
  k = cl->p->k;
  pc = (pIp->ci)->u.l.savedpc;
  {if (l_unlikely(trap))
    {int luaG_tracecall_ret_0;IPCALL(luaG_tracecall,ipluaG_tracecall_0,.ret = &luaG_tracecall_ret_0);trap = luaG_tracecall_ret_0;}}
  base = (pIp->ci)->func.p + 1;
  /* main loop of interpreter */
  for (;;) {
    Instruction i;  /* instruction being executed */
    {vmfetch();}
    #if 0
    { /* low-level line tracing for debugging Lua */
      #include "lopnames.h"
      int pcrel;{pcrel = pcRel(pc, cl->p);}
      {printf("line: %d; %s (%d)\n", luaG_getfuncline(cl->p, pcrel),
             opnames[GET_OPCODE(i)], pcrel);}
    }
    #endif
    {lua_assert(base == pIp->ci->func.p + 1);}
    {lua_assert(base <= pIp->L->top.p && pIp->L->top.p <= pIp->L->stack_last.p);}
    /* for tests, invalidate top for instructions not expecting it */
    {lua_assert(luaP_isIT(i) || (cast_void(pIp->L->top.p = base), 1));}
    vmdispatch (GET_OPCODE(i)) {
      vmcase(OP_MOVE) {
        StkId ra;{ra = RA(i);}
        {setobjs2s(pIp->L, ra, RB(i));}
        vmbreak;
      }
      vmcase(OP_LOADI) {
        StkId ra;{ra = RA(i);}
        lua_Integer b;{b = GETARG_sBx(i);}
        {setivalue(s2v(ra), b);}
        vmbreak;
      }
      vmcase(OP_LOADF) {
        StkId ra;{ra = RA(i);}
        int b;{b = GETARG_sBx(i);}
        {setfltvalue(s2v(ra), cast_num(b));}
        vmbreak;
      }
      vmcase(OP_LOADK) {
        StkId ra;{ra = RA(i);}
        TValue rb;{rb = k + GETARG_Bx(i);}
        {setobj2s(pIp->L, ra, rb);}
        vmbreak;
      }
      vmcase(OP_LOADKX) {
        StkId ra;{ra = RA(i);}
        TValue *rb;
        {rb = k + GETARG_Ax(*pc);} pc++;
        {setobj2s(pIp->L, ra, rb);}
        vmbreak;
      }
      vmcase(OP_LOADFALSE) {
        StkId ra;{ra = RA(i);}
        {setbfvalue(s2v(ra));}
        vmbreak;
      }
      vmcase(OP_LFALSESKIP) {
        StkId ra;{ra = RA(i);}
        {setbfvalue(s2v(ra));}
        pc++;  /* skip next instruction */
        vmbreak;
      }
      vmcase(OP_LOADTRUE) {
        StkId ra;{ra = RA(i);}
        {setbtvalue(s2v(ra));}
        vmbreak;
      }
      vmcase(OP_LOADNIL) {
        StkId ra;{ra = RA(i);}
        int b;{b = GETARG_B(i);}
        do {
          {setnilvalue(s2v(ra++));}
        } while (b--);
        vmbreak;
      }
      vmcase(OP_GETUPVAL) {
        StkId ra;{ra = RA(i);}
        int b;{b = GETARG_B(i);}
        {setobj2s(pIp->L, ra, cl->upvals[b]->v.p);}
        vmbreak;
      }
      vmcase(OP_SETUPVAL) {
        StkId ra;{ra = RA(i);}
        UpVal uv;{uv = cl->upvals[GETARG_B(i)];}
        {setobj(pIp->L, uv->v.p, s2v(ra));}
        {luaC_barrier(pIp->L, uv, s2v(ra));}
        vmbreak;
      }
      vmcase(OP_GETTABUP) {
        StkId ra;{ra = RA(i);}
        TValue upval;{upval = cl->upvals[GETARG_B(i)]->v.p;}
        TValue rc;{rc = KC(i);}
        TString key;{key = tsvalue(rc);}  /* key must be a short string */
        lu_byte tag;
        {luaV_fastget(upval, key, s2v(ra), luaH_getshortstr, tag);}
        {if (tagisempty(tag))
          {lu_byte luaV_finishget_ret_0;IPCALL(luaV_finishget,ipluaV_finishget_0,.L = pIp->L,.t = upval,.key = rc,.val = ra,.tag = tag,.ret = &luaV_finishget_ret_0);Protect(luaV_finishget(pIp->L, upval, rc, ra, tag));}}
        vmbreak;
      }
      vmcase(OP_GETTABLE) {
        StkId ra;{ra = RA(i);}
        TValue rb;{rb = vRB(i);}
        TValue rc;{rc = vRC(i);}
        lu_byte tag;
        {if (ttisinteger(rc)) {  /* fast track for integers? */
          {luaV_fastgeti(rb, ivalue(rc), s2v(ra), tag);}
        }
        else
          {luaV_fastget(rb, rc, s2v(ra), luaH_get, tag);}}
        {if (tagisempty(tag))
          {lu_byte luaV_finishget_ret_4;IPCALL(luaV_finishget,ipluaV_finishget_4,.L = pIp->L,.t = rb,.key = rc,.val = ra,.tag = tag,.ret = &luaV_finishget_ret_4);Protect(luaV_finishget(pIp->L, rb, rc, ra, tag));}}
        vmbreak;
      }
      vmcase(OP_GETI) {
        StkId ra;{ra = RA(i);}
        TValue rb;{rb = vRB(i);}
        int c;{c = GETARG_C(i);}
        lu_byte tag;
        {luaV_fastgeti(rb, c, s2v(ra), tag);}
        {if (tagisempty(tag)) {
          TValue key;
          {setivalue(&key, c);}
          {lu_byte luaV_finishget_ret_1;IPCALL(luaV_finishget,ipluaV_finishget_1,.L = pIp->L,.t = rb,.key = &key,.val = ra,.tag = tag,.ret = &luaV_finishget_ret_1);Protect(luaV_finishget(pIp->L, rb, &key, ra, tag));}
        }}
        vmbreak;
      }
      vmcase(OP_GETFIELD) {
        StkId ra;{ra = RA(i);}
        TValue rb;{rb = vRB(i);}
        TValue rc;{rc = KC(i);}
        TString key;{key = tsvalue(rc);}  /* key must be a short string */
        lu_byte tag;
        {luaV_fastget(rb, key, s2v(ra), luaH_getshortstr, tag);}
        {if (tagisempty(tag))
          {lu_byte luaV_finishget_ret_3;IPCALL(luaV_finishget,ipluaV_finishget_3,.L = pIp->L,.t = rb,.key = rc,.val = ra,.tag = tag,.ret = &luaV_finishget_ret_3);Protect(luaV_finishget(pIp->L, rb, rc, ra, tag));}}
        vmbreak;
      }
      vmcase(OP_SETTABUP) {
        int hres;
        TValue upval;{upval = cl->upvals[GETARG_A(i)]->v.p;}
        TValue rb;{rb = KB(i);}
        TValue rc;{rc = RKC(i);}
        TString key;{key = tsvalue(rb);}  /* key must be a short string */
        {luaV_fastset(upval, key, rc, hres, luaH_psetshortstr);}
        if (hres == HOK)
          {luaV_finishfastset(pIp->L, upval, rc);}
        else
          {IPCALL(luaV_finishset,ipluaV_finishset_0,.L = pIp->L,.t = upval,.key = rb,.val = rc,.aux = hres);Protect(luaV_finishset(pIp->L, upval, rb, rc, hres));}
        vmbreak;
      }
      vmcase(OP_SETTABLE) {
        StkId ra;{ra = RA(i);}
        int hres;
        TValue rb;{rb = vRB(i);}  /* key (table is in 'ra') */
        TValue rc;{rc = RKC(i);}  /* value */
        {if (ttisinteger(rb)) {  /* fast track for integers? */
          {luaV_fastseti(s2v(ra), ivalue(rb), rc, hres);}
        }
        else {
          {luaV_fastset(s2v(ra), rb, rc, hres, luaH_pset);}
        }}
        if (hres == HOK)
          {luaV_finishfastset(pIp->L, s2v(ra), rc);}
        else
          {Protect(luaV_finishset(pIp->L, s2v(ra), rb, rc, hres));}
        vmbreak;
      }
      vmcase(OP_SETI) {
        StkId ra;{ra = RA(i);}
        int hres;
        int b;{b = GETARG_B(i);}
        TValue rc;{rc = RKC(i);}
        {luaV_fastseti(s2v(ra), b, rc, hres);}
        if (hres == HOK)
          {luaV_finishfastset(pIp->L, s2v(ra), rc);}
        else {
          TValue key;
          {setivalue(&key, b);}
          {Protect(luaV_finishset(pIp->L, s2v(ra), &key, rc, hres));}
        }
        vmbreak;
      }
      vmcase(OP_SETFIELD) {
        StkId ra;{ra = RA(i);}
        int hres;
        TValue rb;{rb = KB(i);}
        TValue rc;{rc = RKC(i);}
        TString key;{key = tsvalue(rb);}  /* key must be a short string */
        {luaV_fastset(s2v(ra), key, rc, hres, luaH_psetshortstr);}
        if (hres == HOK)
          {luaV_finishfastset(pIp->L, s2v(ra), rc);}
        else
          {Protect(luaV_finishset(pIp->L, s2v(ra), rb, rc, hres));}
        vmbreak;
      }
      vmcase(OP_NEWTABLE) {
        StkId ra;{ra = RA(i);}
        unsigned b;{b = cast_uint(GETARG_vB(i));}  /* log2(hash size) + 1 */
        unsigned c;{c = cast_uint(GETARG_vC(i));}  /* array size */
        Table *t;
        if (b > 0)
          b = 1u << (b - 1);  /* hash size is 2^(b - 1) */
        {if (TESTARG_k(i)) {  /* non-zero extra argument? */
          {lua_assert(GETARG_Ax(*pc) != 0);}
          /* add it to array size */
          {c += cast_uint(GETARG_Ax(*pc)) * (MAXARG_vC + 1);}
        }}
        pc++;  /* skip extra argument */
        (pIp->L)->top.p = ra + 1;  /* correct top in case of emergency GC */
        {Table * luaH_new_ret_0;IPCALL(luaH_new,ipluaH_new_0,.ret = luaH_new_ret_0);t = luaH_new_ret_0;}  /* memory allocation */
        {sethvalue2s(pIp->L, ra, t);}
        if (b != 0 || c != 0)
          {IPCALL(luaH_resize,ipluaH_resize_0);}  /* idem */
        {checkGC(pIp->L, ra + 1);}
        vmbreak;
      }
      vmcase(OP_SELF) {
        StkId ra;{ra = RA(i);}
        lu_byte tag;
        TValue rb;{rb = vRB(i);}
        TValue rc;{rc = KC(i);}
        TString key;{key = tsvalue(rc);}  /* key must be a short string */
        {setobj2s(pIp->L, ra + 1, rb);}
        {luaV_fastget(rb, key, s2v(ra), luaH_getshortstr, tag);}
        {if (tagisempty(tag))
          {lu_byte luaV_finishget_ret_2;IPCALL(luaV_finishget,ipluaV_finishget_2,.L = pIp->L,.t = rb,.key = rc,.val = ra,.tag = tag,.ret = &luaV_finishget_ret_2);Protect(luaV_finishget(pIp->L, rb, rc, ra, tag));}}
        vmbreak;
      }
      vmcase(OP_ADDI) {
        {op_arithI(pIp->L, l_addi, luai_numadd);}
        vmbreak;
      }
      vmcase(OP_ADDK) {
        {op_arithK(pIp->L, l_addi, luai_numadd);}
        vmbreak;
      }
      vmcase(OP_SUBK) {
        {op_arithK(pIp->L, l_subi, luai_numsub);}
        vmbreak;
      }
      vmcase(OP_MULK) {
        {op_arithK(pIp->L, l_muli, luai_nummul);}
        vmbreak;
      }
      vmcase(OP_MODK) {
        {savestate(pIp->L, pIp->ci);}  /* in case of division by 0 */
        {op_arithK(pIp->L, luaV_mod, luaV_modf);}
        vmbreak;
      }
      vmcase(OP_POWK) {
        {op_arithfK(pIp->L, luai_numpow);}
        vmbreak;
      }
      vmcase(OP_DIVK) {
        {op_arithfK(pIp->L, luai_numdiv);}
        vmbreak;
      }
      vmcase(OP_IDIVK) {
        {savestate(pIp->L, pIp->ci);}  /* in case of division by 0 */
        {op_arithK(pIp->L, luaV_idiv, luai_numidiv);}
        vmbreak;
      }
      vmcase(OP_BANDK) {
        {op_bitwiseK(pIp->L, l_band);}
        vmbreak;
      }
      vmcase(OP_BORK) {
        {op_bitwiseK(pIp->L, l_bor);}
        vmbreak;
      }
      vmcase(OP_BXORK) {
        {op_bitwiseK(pIp->L, l_bxor);}
        vmbreak;
      }
      vmcase(OP_SHRI) {
        StkId ra;{ra = RA(i);}
        TValue rb;{rb = vRB(i);}
        int ic;{ic = GETARG_sC(i);}
        lua_Integer ib;
        {if (tointegerns(rb, &ib)) {
          pc++; {setivalue(s2v(ra), luaV_shiftl(ib, -ic));}
        }}
        vmbreak;
      }
      vmcase(OP_SHLI) {
        StkId ra;{ra = RA(i);}
        TValue rb;{rb = vRB(i);}
        int ic;{ic = GETARG_sC(i);}
        lua_Integer ib;
        {if (tointegerns(rb, &ib)) {
          pc++; {setivalue(s2v(ra), luaV_shiftl(ic, ib));}
        }}
        vmbreak;
      }
      vmcase(OP_ADD) {
        {op_arith(pIp->L, l_addi, luai_numadd);}
        vmbreak;
      }
      vmcase(OP_SUB) {
        {op_arith(pIp->L, l_subi, luai_numsub);}
        vmbreak;
      }
      vmcase(OP_MUL) {
        {op_arith(pIp->L, l_muli, luai_nummul);}
        vmbreak;
      }
      vmcase(OP_MOD) {
        {savestate(pIp->L, pIp->ci);}  /* in case of division by 0 */
        {op_arith(pIp->L, luaV_mod, luaV_modf);}
        vmbreak;
      }
      vmcase(OP_POW) {
        {op_arithf(pIp->L, luai_numpow);}
        vmbreak;
      }
      vmcase(OP_DIV) {  /* float division (always with floats) */
        {op_arithf(pIp->L, luai_numdiv);}
        vmbreak;
      }
      vmcase(OP_IDIV) {  /* floor division */
        {savestate(pIp->L, pIp->ci);}  /* in case of division by 0 */
        {op_arith(pIp->L, luaV_idiv, luai_numidiv);}
        vmbreak;
      }
      vmcase(OP_BAND) {
        {op_bitwise(pIp->L, l_band);}
        vmbreak;
      }
      vmcase(OP_BOR) {
        {op_bitwise(pIp->L, l_bor);}
        vmbreak;
      }
      vmcase(OP_BXOR) {
        {op_bitwise(pIp->L, l_bxor);}
        vmbreak;
      }
      vmcase(OP_SHR) {
        {op_bitwise(pIp->L, luaV_shiftr);}
        vmbreak;
      }
      vmcase(OP_SHL) {
        {op_bitwise(pIp->L, luaV_shiftl);}
        vmbreak;
      }
      vmcase(OP_MMBIN) {
        StkId ra;{ra = RA(i);}
        Instruction pi = *(pc - 2);  /* original arith. expression */
        TValue rb;{rb = vRB(i);}
        TMS tm;{tm = (TMS)GETARG_C(i);}
        StkId result;{result = RA(pi);}
        {lua_assert(OP_ADD <= GET_OPCODE(pi) && GET_OPCODE(pi) <= OP_SHR);}
        {Protect(luaT_trybinTM(pIp->L, s2v(ra), rb, result, tm));}
        vmbreak;
      }
      vmcase(OP_MMBINI) {
        StkId ra;{ra = RA(i);}
        Instruction pi = *(pc - 2);  /* original arith. expression */
        int imm;{imm = GETARG_sB(i);}
        TMS tm;{tm = (TMS)GETARG_C(i);}
        int flip;{flip = GETARG_k(i);}
        StkId result;{result = RA(pi);}
        {Protect(luaT_trybiniTM(pIp->L, s2v(ra), imm, flip, result, tm));}
        vmbreak;
      }
      vmcase(OP_MMBINK) {
        StkId ra;{ra = RA(i);}
        Instruction pi = *(pc - 2);  /* original arith. expression */
        TValue imm;{imm = KB(i);}
        TMS tm;{tm = (TMS)GETARG_C(i);}
        int flip;{flip = GETARG_k(i);}
        StkId result;{result = RA(pi);}
        {Protect(luaT_trybinassocTM(pIp->L, s2v(ra), imm, flip, result, tm));}
        vmbreak;
      }
      vmcase(OP_UNM) {
        StkId ra;{ra = RA(i);}
        TValue rb;{rb = vRB(i);}
        lua_Number nb;
        {if (ttisinteger(rb)) {
          lua_Integer ib;{ib = ivalue(rb);}
          {setivalue(s2v(ra), intop(-, 0, ib));}
        }
        else {if (tonumberns(rb, nb)) {
          {setfltvalue(s2v(ra), luai_numunm(pIp->L, nb));}
        }
        else
          {IPCALL(luaT_trybinTM,ipluaT_trybinTM_0,.L = pIp->L,.p1 = rb,.p2 = rb,.res = ra,.event = TM_UNM);Protect(luaT_trybinTM(pIp->L, rb, rb, ra, TM_UNM));}}}
        vmbreak;
      }
      vmcase(OP_BNOT) {
        StkId ra;{ra = RA(i);}
        TValue rb;{rb = vRB(i);}
        lua_Integer ib;
        {if (tointegerns(rb, &ib)) {
          {setivalue(s2v(ra), intop(^, ~l_castS2U(0), ib));}
        }
        else
          {IPCALL(luaT_trybinTM,ipluaT_trybinTM_1,.L = pIp->L,.p1 = rb,.p2 = rb,.res = ra,.event = TM_BNOT);Protect(luaT_trybinTM(pIp->L, rb, rb, ra, TM_BNOT));}}
        vmbreak;
      }
      vmcase(OP_NOT) {
        StkId ra;{ra = RA(i);}
        TValue rb;{rb = vRB(i);}
        {if (l_isfalse(rb))
          {setbtvalue(s2v(ra));}
        else
          {setbfvalue(s2v(ra));}}
        vmbreak;
      }
      vmcase(OP_LEN) {
        StkId ra;{ra = RA(i);}
        {Protect(luaV_objlen(pIp->L, ra, vRB(i)));}
        vmbreak;
      }
      vmcase(OP_CONCAT) {
        StkId ra;{ra = RA(i);}
        int n;{n = GETARG_B(i);}  /* number of elements to concatenate */
        (pIp->L)->top.p = ra + n;  /* mark the end of concat operands */
        {IPCALL(luaV_concat,ipluaV_concat_0,.L = pIp->L,.total = n);ProtectNT(luaV_concat(pIp->L, n));}
        {checkGC(pIp->L, pIp->L->top.p);} /* 'luaV_concat' ensures correct top */
        vmbreak;
      }
      vmcase(OP_CLOSE) {
        StkId ra;{ra = RA(i);}
        {lua_assert(!GETARG_B(i));}  /* 'close must be alive */
        {StkId luaF_close_ret_0;IPCALL(luaF_close,ipluaF_close_0,.L = pIp->L,.level = ra,.status = LUA_OK,.yy = 1,.ret = &luaF_close_ret_0);Protect(luaF_close(pIp->L, ra, LUA_OK, 1));}
        vmbreak;
      }
      vmcase(OP_TBC) {
        StkId ra;{ra = RA(i);}
        /* create new to-be-closed upvalue */
        {IPCALL(luaF_newtbcupval,ipluaF_newtbcupval_0,.L = pIp->L,.level = ra);halfProtect(luaF_newtbcupval(pIp->L, ra));}
        vmbreak;
      }
      vmcase(OP_JMP) {
        {dojump(pIp->ci, i, 0);}
        vmbreak;
      }
      vmcase(OP_EQ) {
        StkId ra;{ra = RA(i);}
        int cond;
        TValue rb;{rb = vRB(i);}
        {Protect(cond = luaV_equalobj(pIp->L, s2v(ra), rb));}
        {docondjump();}
        vmbreak;
      }
      vmcase(OP_LT) {
        {op_order(pIp->L, l_lti, LTnum, lessthanothers);}
        vmbreak;
      }
      vmcase(OP_LE) {
        {op_order(pIp->L, l_lei, LEnum, lessequalothers);}
        vmbreak;
      }
      vmcase(OP_EQK) {
        StkId ra;{ra = RA(i);}
        TValue rb;{rb = KB(i);}
        /* basic types do not use '__eq'; we can use raw equality */
        int cond;{cond = luaV_rawequalobj(s2v(ra), rb);}
        {docondjump();}
        vmbreak;
      }
      vmcase(OP_EQI) {
        StkId ra;{ra = RA(i);}
        int cond;
        int im;{im = GETARG_sB(i);}
        {if (ttisinteger(s2v(ra)))
          {cond = (ivalue(s2v(ra)) == im);}
        else {if (ttisfloat(s2v(ra)))
          {cond = luai_numeq(fltvalue(s2v(ra)), cast_num(im));}
        else
          cond = 0;}}  /* other types cannot be equal to a number */
        {docondjump();}
        vmbreak;
      }
      vmcase(OP_LTI) {
        {op_orderI(pIp->L, l_lti, luai_numlt, 0, TM_LT);}
        vmbreak;
      }
      vmcase(OP_LEI) {
        {op_orderI(pIp->L, l_lei, luai_numle, 0, TM_LE);}
        vmbreak;
      }
      vmcase(OP_GTI) {
        {op_orderI(pIp->L, l_gti, luai_numgt, 1, TM_LT);}
        vmbreak;
      }
      vmcase(OP_GEI) {
        {op_orderI(pIp->L, l_gei, luai_numge, 1, TM_LE);}
        vmbreak;
      }
      vmcase(OP_TEST) {
        StkId ra;{ra = RA(i);}
        int cond;{cond = !l_isfalse(s2v(ra));}
        {docondjump();}
        vmbreak;
      }
      vmcase(OP_TESTSET) {
        StkId ra;{ra = RA(i);}
        TValue rb;{rb = vRB(i);}
        {if (l_isfalse(rb) == GETARG_k(i))
          pc++;
        else {
          {setobj2s(pIp->L, ra, rb);}
          {donextjump(pIp->ci);}
        }}
        vmbreak;
      }
      vmcase(OP_CALL) {
        StkId ra;{ra = RA(i);}
        CallInfo *newci;
        int b;{b = GETARG_B(i);}
        int nresults;{nresults = GETARG_C(i) - 1;}
        if (b != 0)  /* fixed number of arguments? */
          (pIp->L)->top.p = ra + b;  /* top signals number of arguments */
        /* else previous instruction set top */
        {savepc(pIp->L);}  /* in case of errors */
        {CallInfo * luaD_precall_ret_0;IPCALL(luaD_precall,ipluaD_precall_0,.ret = luaD_precall_ret_0);if ((newci = luaD_precall_ret_0) == NULL)
          {updatetrap(pIp->ci);}  /* C call; nothing else to be done */
        else {  /* Lua call: run function in this same C frame */
          (pIp->ci) = newci;
          goto startfunc;
        }}
        vmbreak;
      }
      vmcase(OP_TAILCALL) {
        StkId ra;{ra = RA(i);}
        int b;{b = GETARG_B(i);}  /* number of arguments + 1 (function) */
        int n;  /* number of results when calling a C function */
        int nparams1;{nparams1 = GETARG_C(i);}
        /* delta is virtual 'func' - real 'func' (vararg functions) */
        int delta = (nparams1) ? (pIp->ci)->u.l.nextraargs + nparams1 : 0;
        if (b != 0)
          (pIp->L)->top.p = ra + b;
        else  /* previous instruction set top */
          {b = cast_int(pIp->L->top.p - ra);}
        {savepc(pIp->ci);}  /* several calls here can raise errors */
        {if (TESTARG_k(i)) {
          {IPCALL(luaF_closeupval,ipluaF_closeupval_0);}  /* close upvalues from current call */
          {lua_assert(pIp->L->tbclist.p < base);}  /* no pending tbc variables */
          {lua_assert(base == pIp->ci->func.p + 1);}
        }}
        {int luaD_pretailcall_ret_0;IPCALL(luaD_pretailcall,ipluaD_pretailcall_0,.ret = &luaD_pretailcall_ret_0);if ((n = luaD_pretailcall_ret_0) < 0)  /* Lua function? */
          goto startfunc;  /* execute the callee */
        else {  /* C function? */
          (pIp->ci)->func.p -= delta;  /* restore 'func' (if vararg) */
          {IPCALL(luaD_poscall,ipluaD_poscall_1);}  /* finish caller */
          {updatetrap(pIp->ci);}  /* 'luaD_poscall' can change hooks */
          goto ret;  /* caller returns after the tail call */
        }}
      }
      vmcase(OP_RETURN) {
        StkId ra;{ra = RA(i);}
        int n;{n = GETARG_B(i) - 1;}  /* number of results */
        int nparams1;{nparams1 = GETARG_C(i);}
        if (n < 0)  /* not fixed? */
          {n = cast_int(pIp->L->top.p - ra);}  /* get what is available */
        {savepc(pIp->ci);}
        {if (TESTARG_k(i)) {  /* may there be open upvalues? */
          (pIp->ci)->u2.nres = n;  /* save number of returns */
          if ((pIp->L)->top.p < (pIp->ci)->top.p)
            (pIp->L)->top.p = (pIp->ci)->top.p;
          {StkId luaF_close_ret_1;IPCALL(luaF_close,ipluaF_close_1,.ret = &luaF_close_ret_1);luaF_close_ret_1;}
          {updatetrap(pIp->ci);}
          {updatestack(pIp->ci);}
        }}
        if (nparams1)  /* vararg function? */
          (pIp->ci)->func.p -= (pIp->ci)->u.l.nextraargs + nparams1;
        (pIp->L)->top.p = ra + n;  /* set call for 'luaD_poscall' */
        {IPCALL(luaD_poscall,ipluaD_poscall_2);}
        {updatetrap(pIp->ci);}  /* 'luaD_poscall' can change hooks */
        goto ret;
      }
      vmcase(OP_RETURN0) {
        {if (l_unlikely(pIp->L->hookmask)) {
          StkId ra;{ra = RA(i);}
          (pIp->L)->top.p = ra;
          {savepc(pIp->ci);}
          {IPCALL(luaD_poscall,ipluaD_poscall_3);}  /* no hurry... */
          trap = 1;
        }
        else {  /* do the 'poscall' here */
          int nres;{nres = get_nresults(pIp->ci->callstatus);}
          (pIp->L)->ci = (pIp->ci)->previous;  /* back to caller */
          (pIp->L)->top.p = base - 1;
          for (; l_unlikely(nres > 0); nres--)
            {setnilvalue(s2v(pIp->L->top.p++));}  /* all results are nil */
        }}
        goto ret;
      }
      vmcase(OP_RETURN1) {
        {if (l_unlikely(pIp->L->hookmask)) {
          StkId ra;{ra = RA(i);}
          (pIp->L)->top.p = ra + 1;
          {savepc(pIp->ci);}
          {IPCALL(luaD_poscall,ipluaD_poscall_0);}  /* no hurry... */
          trap = 1;
        }
        else {  /* do the 'poscall' here */
          int nres;{nres = get_nresults(pIp->ci->callstatus);}
          (pIp->L)->ci = (pIp->ci)->previous;  /* back to caller */
          if (nres == 0)
            (pIp->L)->top.p = base - 1;  /* asked for no results */
          else {
            StkId ra;{ra = RA(i);}
            {setobjs2s(pIp->L, base - 1, ra);}  /* at least this result */
            (pIp->L)->top.p = base;
            for (; l_unlikely(nres > 1); nres--)
              {setnilvalue(s2v(pIp->L->top.p++));}  /* complete missing results */
          }
        }}
       ret:  /* return from a Lua function */
        if ((pIp->ci)->callstatus & CIST_FRESH)
          return;  /* end this frame */
        else {
          (pIp->ci) = (pIp->ci)->previous;
          goto returning;  /* continue running caller in this frame */
        }
      }
      vmcase(OP_FORLOOP) {
        StkId ra;{ra = RA(i);}
        {if (ttisinteger(s2v(ra + 1))) {  /* integer loop? */
          lua_Unsigned count;{count = l_castS2U(ivalue(s2v(ra)));}
          if (count > 0) {  /* still more iterations? */
            lua_Integer step;{step = ivalue(s2v(ra + 1));}
            lua_Integer idx;{idx = ivalue(s2v(ra + 2));}  /* control variable */
            {chgivalue(s2v(ra), l_castU2S(count - 1));}  /* update counter */
            {idx = intop(+, idx, step);}  /* add step to index */
            {chgivalue(s2v(ra + 2), idx);}  /* update control variable */
            {pc -= GETARG_Bx(i);}  /* jump back */
          }
        }
        else {int floatforloop_ret_0;IPCALL(floatforloop,ipfloatforloop_0,.ra = ra,.ret = &floatforloop_ret_0);if (floatforloop_ret_0)  /* float loop */
          {pc -= GETARG_Bx(i);}}}  /* jump back */
        {updatetrap(pIp->ci);}  /* allows a signal to break the loop */
        vmbreak;
      }
      vmcase(OP_FORPREP) {
        StkId ra;{ra = RA(i);}
        {savestate(pIp->L, pIp->ci);}  /* in case of errors */
        {int forprep_ret_0;IPCALL(forprep,ipforprep_0,.L = pIp->L,.ra = ra,.ret = &forprep_ret_0);if (forprep_ret_0)
          {pc += GETARG_Bx(i) + 1;}}  /* skip the loop */
        vmbreak;
      }
      vmcase(OP_TFORPREP) {
       /* before: 'ra' has the iterator function, 'ra + 1' has the state,
          'ra + 2' has the initial value for the control variable, and
          'ra + 3' has the closing variable. This opcode then swaps the
          control and the closing variables and marks the closing variable
          as to-be-closed.
       */
       StkId ra;{ra = RA(i);}
       TValue temp;  /* to swap control and closing variables */
       {setobj(pIp->L, &temp, s2v(ra + 3));}
       {setobjs2s(pIp->L, ra + 3, ra + 2);}
       {setobj2s(pIp->L, ra + 2, &temp);}
        /* create to-be-closed upvalue (if closing var. is not nil) */
        {IPCALL(luaF_newtbcupval,ipluaF_newtbcupval_1,.L = pIp->L,.level = ra + 2);halfProtect(luaF_newtbcupval(pIp->L, ra + 2));}
        {pc += GETARG_Bx(i);}  /* go to end of the loop */
        i = *(pc++);  /* fetch next instruction */
        {lua_assert(GET_OPCODE(i) == OP_TFORCALL && ra == RA(i));}
        goto l_tforcall;
      }
      vmcase(OP_TFORCALL) {
       l_tforcall: {
        /* 'ra' has the iterator function, 'ra + 1' has the state,
           'ra + 2' has the closing variable, and 'ra + 3' has the control
           variable. The call will use the stack starting at 'ra + 3',
           so that it preserves the first three values, and the first
           return will be the new value for the control variable.
        */
        StkId ra;{ra = RA(i);}
        {setobjs2s(pIp->L, ra + 5, ra + 3);}  /* copy the control variable */
        {setobjs2s(pIp->L, ra + 4, ra + 1);}  /* copy state */
        {setobjs2s(pIp->L, ra + 3, ra);}  /* copy function */
        (pIp->L)->top.p = ra + 3 + 3;
        {ProtectNT(luaD_call(pIp->L, ra + 3, GETARG_C(i)));}  /* do the call */
        {updatestack(pIp->ci);}  /* stack may have changed */
        i = *(pc++);  /* go to next instruction */
        {lua_assert(GET_OPCODE(i) == OP_TFORLOOP && ra == RA(i));}
        goto l_tforloop;
      }}
      vmcase(OP_TFORLOOP) {
       l_tforloop: {
        StkId ra;{ra = RA(i);}
        {if (!ttisnil(s2v(ra + 3)))  /* continue loop? */
          {pc -= GETARG_Bx(i);}}  /* jump back */
        vmbreak;
      }}
      vmcase(OP_SETLIST) {
        StkId ra;{ra = RA(i);}
        unsigned n;{n = cast_uint(GETARG_vB(i));}
        unsigned int last;{last = cast_uint(GETARG_vC(i));}
        Table h;{h = hvalue(s2v(ra));}
        if (n == 0)
          {n = cast_uint(pIp->L->top.p - ra) - 1;}  /* get up to the top */
        else
          (pIp->L)->top.p = (pIp->ci)->top.p;  /* correct top in case of emergency GC */
        last += n;
        {if (TESTARG_k(i)) {
          {last += cast_uint(GETARG_Ax(*pc)) * (MAXARG_vC + 1);}
          pc++;
        }}
        /* when 'n' is known, table should have proper size */
        if (last > h->asize) {  /* needs more space? */
          /* fixed-size sets should have space preallocated */
          {lua_assert(GETARG_vB(i) == 0);}
          {IPCALL(luaH_resizearray,ipluaH_resizearray_0);}  /* preallocate it at once */
        }
        for (; n > 0; n--) {
          TValue val;{val = s2v(ra + n);}
          {obj2arr(h, last - 1, val);}
          last--;
          {luaC_barrierback(pIp->L, obj2gco(h), val);}
        }
        vmbreak;
      }
      vmcase(OP_CLOSURE) {
        StkId ra;{ra = RA(i);}
        Proto p;{p = cl->p->p[GETARG_Bx(i)];}
        {IPCALL(pushclosure,ippushclosure_0,.L = pIp->L,.p = p,.encup = cl->upvals,.base = base,.ra = ra);halfProtect(pushclosure(pIp->L, p, cl->upvals, base, ra));}
        {checkGC(pIp->L, ra + 1);}
        vmbreak;
      }
      vmcase(OP_VARARG) {
        StkId ra;{ra = RA(i);}
        int n;{n = GETARG_C(i) - 1;}  /* required results */
        {IPCALL(luaT_getvarargs,ipluaT_getvarargs_0,.L = pIp->L,.ci = pIp->ci,.where = ra,.wanted = n);Protect(luaT_getvarargs(pIp->L, pIp->ci, ra, n));}
        vmbreak;
      }
      vmcase(OP_VARARGPREP) {
        {ProtectNT(luaT_adjustvarargs(pIp->L, GETARG_A(i), pIp->ci, cl->p));}
        {if (l_unlikely(trap)) {  /* previous "Protect" updated trap */
          {IPCALL(luaD_hookcall,ipluaD_hookcall_0);}
          (pIp->L)->oldpc = 1;  /* next opcode will be seen as a "new" line */
        }}
        {updatebase(pIp->ci);}  /* function has new base after adjustment */
        vmbreak;
      }
      vmcase(OP_EXTRAARG) {
        {lua_assert(0);}
        vmbreak;
      }
    }
  }
}