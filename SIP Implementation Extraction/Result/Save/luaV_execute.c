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
  trap = pIp -> L->hookmask;
 returning:  /* trap already set */
  cl = ci_func(pIp -> ci);
  k = cl->p->k;
  pc = pIp -> ci->u.l.savedpc;
  if (l_unlikely(trap))
    trap = {int luaG_tracecall_ret_93;IPCALL(luaG_tracecall,ipluaG_tracecall_0,.ret = &luaG_tracecall_ret_93);}
  base = pIp -> ci->func.p + 1;
  /* main loop of interpreter */
  for (;;) {
    Instruction i;  /* instruction being executed */
    vmfetch();
    #if 0
    { /* low-level line tracing for debugging Lua */
      #include "lopnames.h"
      int pcrel = pcRel(pc, cl->p);
      printf("line: %d; %s (%d)\n", luaG_getfuncline(cl->p, pcrel),
             opnames[GET_OPCODE(i)], pcrel);
    }
    #endif
    lua_assert(base == pIp -> ci->func.p + 1);
    lua_assert(base <= pIp -> L->top.p && pIp -> L->top.p <= pIp -> L->stack_last.p);
    /* for tests, invalidate top for instructions not expecting it */
    lua_assert(luaP_isIT(i) || (cast_void(pIp -> L->top.p = base), 1));
    vmdispatch (GET_OPCODE(i)) {
      vmcase(OP_MOVE) {
        StkId ra = RA(i);
        setobjs2s(pIp -> L, ra, RB(i));
        {int luaG_traceexec_ret_92;IPCALL(luaG_traceexec,ipluaG_traceexec_76,.ret = &luaG_traceexec_ret_92);luaG_traceexec_ret_92;}
      }
      vmcase(OP_LOADI) {
        StkId ra = RA(i);
        lua_Integer b = GETARG_sBx(i);
        setivalue(s2v(ra), b);
        {int luaG_traceexec_ret_91;IPCALL(luaG_traceexec,ipluaG_traceexec_75,.ret = &luaG_traceexec_ret_91);luaG_traceexec_ret_91;}
      }
      vmcase(OP_LOADF) {
        StkId ra = RA(i);
        int b = GETARG_sBx(i);
        setfltvalue(s2v(ra), cast_num(b));
        {int luaG_traceexec_ret_90;IPCALL(luaG_traceexec,ipluaG_traceexec_74,.ret = &luaG_traceexec_ret_90);luaG_traceexec_ret_90;}
      }
      vmcase(OP_LOADK) {
        StkId ra = RA(i);
        TValue *rb = k + GETARG_Bx(i);
        setobj2s(pIp -> L, ra, rb);
        {int luaG_traceexec_ret_89;IPCALL(luaG_traceexec,ipluaG_traceexec_73,.ret = &luaG_traceexec_ret_89);luaG_traceexec_ret_89;}
      }
      vmcase(OP_LOADKX) {
        StkId ra = RA(i);
        TValue *rb;
        rb = k + GETARG_Ax(*pc); pc++;
        setobj2s(pIp -> L, ra, rb);
        {int luaG_traceexec_ret_88;IPCALL(luaG_traceexec,ipluaG_traceexec_72,.ret = &luaG_traceexec_ret_88);luaG_traceexec_ret_88;}
      }
      vmcase(OP_LOADFALSE) {
        StkId ra = RA(i);
        setbfvalue(s2v(ra));
        {int luaG_traceexec_ret_87;IPCALL(luaG_traceexec,ipluaG_traceexec_71,.ret = &luaG_traceexec_ret_87);luaG_traceexec_ret_87;}
      }
      vmcase(OP_LFALSESKIP) {
        StkId ra = RA(i);
        setbfvalue(s2v(ra));
        pc++;  /* skip next instruction */
        {int luaG_traceexec_ret_86;IPCALL(luaG_traceexec,ipluaG_traceexec_70,.ret = &luaG_traceexec_ret_86);luaG_traceexec_ret_86;}
      }
      vmcase(OP_LOADTRUE) {
        StkId ra = RA(i);
        setbtvalue(s2v(ra));
        {int luaG_traceexec_ret_85;IPCALL(luaG_traceexec,ipluaG_traceexec_69,.ret = &luaG_traceexec_ret_85);luaG_traceexec_ret_85;}
      }
      vmcase(OP_LOADNIL) {
        StkId ra = RA(i);
        int b = GETARG_B(i);
        do {
          setnilvalue(s2v(ra++));
        } while (b--);
        {int luaG_traceexec_ret_84;IPCALL(luaG_traceexec,ipluaG_traceexec_68,.ret = &luaG_traceexec_ret_84);luaG_traceexec_ret_84;}
      }
      vmcase(OP_GETUPVAL) {
        StkId ra = RA(i);
        int b = GETARG_B(i);
        setobj2s(pIp -> L, ra, cl->upvals[b]->v.p);
        {int luaG_traceexec_ret_83;IPCALL(luaG_traceexec,ipluaG_traceexec_67,.ret = &luaG_traceexec_ret_83);luaG_traceexec_ret_83;}
      }
      vmcase(OP_SETUPVAL) {
        StkId ra = RA(i);
        UpVal *uv = cl->upvals[GETARG_B(i)];
        setobj(pIp -> L, uv->v.p, s2v(ra));
        luaC_barrier(pIp -> L, uv, s2v(ra));
        {int luaG_traceexec_ret_82;IPCALL(luaG_traceexec,ipluaG_traceexec_66,.ret = &luaG_traceexec_ret_82);luaG_traceexec_ret_82;}
      }
      vmcase(OP_GETTABUP) {
        StkId ra = RA(i);
        TValue *upval = cl->upvals[GETARG_B(i)]->v.p;
        TValue *rc = KC(i);
        TString *key = tsvalue(rc);  /* key must be a short string */
        lu_byte tag;
        luaV_fastget(upval, key, s2v(ra), luaH_getshortstr, tag);
        if (tagisempty(tag))
          {lu_byte luaV_finishget_ret_81;IPCALL(luaV_finishget,ipluaV_finishget_3,.ret = &luaV_finishget_ret_81);}rotect(luaV_finishget(pIp -> L, upval, rc, ra, tag));
        {int luaG_traceexec_ret_80;IPCALL(luaG_traceexec,ipluaG_traceexec_65,.ret = &luaG_traceexec_ret_80);luaG_traceexec_ret_80;}
      }
      vmcase(OP_GETTABLE) {
        StkId ra = RA(i);
        TValue *rb = vRB(i);
        TValue *rc = vRC(i);
        lu_byte tag;
        if (ttisinteger(rc)) {  /* fast track for integers? */
          luaV_fastgeti(rb, ivalue(rc), s2v(ra), tag);
        }
        else
          luaV_fastget(rb, rc, s2v(ra), luaH_get, tag);
        if (tagisempty(tag))
          Protect(luaV_finishget(pIp -> L, rb, rc, ra, tag));
        {int luaG_traceexec_ret_79;IPCALL(luaG_traceexec,ipluaG_traceexec_64,.ret = &luaG_traceexec_ret_79);luaG_traceexec_ret_79;}
      }
      vmcase(OP_GETI) {
        StkId ra = RA(i);
        TValue *rb = vRB(i);
        int c = GETARG_C(i);
        lu_byte tag;
        luaV_fastgeti(rb, c, s2v(ra), tag);
        if (tagisempty(tag)) {
          TValue key;
          setivalue(&key, c);
          {lu_byte luaV_finishget_ret_78;IPCALL(luaV_finishget,ipluaV_finishget_2,.ret = &luaV_finishget_ret_78);luaV_finishget_ret_78PluaV_finishget_ret_78rluaV_finishget_ret_78oluaV_finishget_ret_78tluaV_finishget_ret_78eluaV_finishget_ret_78cluaV_finishget_ret_78tluaV_finishget_ret_78(luaV_finishget_ret_78lluaV_finishget_ret_78uluaV_finishget_ret_78aluaV_finishget_ret_78VluaV_finishget_ret_78_luaV_finishget_ret_78fluaV_finishget_ret_78iluaV_finishget_ret_78nluaV_finishget_ret_78iluaV_finishget_ret_78sluaV_finishget_ret_78hluaV_finishget_ret_78gluaV_finishget_ret_78eluaV_finishget_ret_78tluaV_finishget_ret_78(luaV_finishget_ret_78LluaV_finishget_ret_78,luaV_finishget_ret_78 luaV_finishget_ret_78rluaV_finishget_ret_78bluaV_finishget_ret_78,luaV_finishget_ret_78 luaV_finishget_ret_78&luaV_finishget_ret_78kluaV_finishget_ret_78eluaV_finishget_ret_78yluaV_finishget_ret_78,luaV_finishget_ret_78 luaV_finishget_ret_78rluaV_finishget_ret_78aluaV_finishget_ret_78,luaV_finishget_ret_78 luaV_finishget_ret_78tluaV_finishget_ret_78aluaV_finishget_ret_78gluaV_finishget_ret_78)luaV_finishget_ret_78)luaV_finishget_ret_78;}
        }
        {int luaG_traceexec_ret_77;IPCALL(luaG_traceexec,ipluaG_traceexec_63,.ret = &luaG_traceexec_ret_77);luaG_traceexec_ret_77;}
      }
      vmcase(OP_GETFIELD) {
        StkId ra = RA(i);
        TValue *rb = vRB(i);
        TValue *rc = KC(i);
        TString *key = tsvalue(rc);  /* key must be a short string */
        lu_byte tag;
        luaV_fastget(rb, key, s2v(ra), luaH_getshortstr, tag);
        if (tagisempty(tag))
          {lu_byte luaV_finishget_ret_76;IPCALL(luaV_finishget,ipluaV_finishget_1,.ret = &luaV_finishget_ret_76);}rotect(luaV_finishget(pIp -> L, rb, rc, ra, tag));
        {int luaG_traceexec_ret_75;IPCALL(luaG_traceexec,ipluaG_traceexec_62,.ret = &luaG_traceexec_ret_75);luaG_traceexec_ret_75;}
      }
      vmcase(OP_SETTABUP) {
        int hres;
        TValue *upval = cl->upvals[GETARG_A(i)]->v.p;
        TValue *rb = KB(i);
        TValue *rc = RKC(i);
        TString *key = tsvalue(rb);  /* key must be a short string */
        luaV_fastset(upval, key, rc, hres, luaH_psetshortstr);
        if (hres == HOK)
          luaV_finishfastset(pIp -> L, upval, rc);
        else
          Protect(luaV_finishset(pIp -> L, upval, rb, rc, hres));
        {int luaG_traceexec_ret_74;IPCALL(luaG_traceexec,ipluaG_traceexec_61,.ret = &luaG_traceexec_ret_74);luaG_traceexec_ret_74;}
      }
      vmcase(OP_SETTABLE) {
        StkId ra = RA(i);
        int hres;
        TValue *rb = vRB(i);  /* key (table is in 'ra') */
        TValue *rc = RKC(i);  /* value */
        if (ttisinteger(rb)) {  /* fast track for integers? */
          luaV_fastseti(s2v(ra), ivalue(rb), rc, hres);
        }
        else {
          luaV_fastset(s2v(ra), rb, rc, hres, luaH_pset);
        }
        if (hres == HOK)
          luaV_finishfastset(pIp -> L, s2v(ra), rc);
        else
          {IPCALL(luaV_finishset,ipluaV_finishset_0);}rotect(luaV_finishset(pIp -> L, s2v(ra), rb, rc, hres));
        {int luaG_traceexec_ret_73;IPCALL(luaG_traceexec,ipluaG_traceexec_60,.ret = &luaG_traceexec_ret_73);luaG_traceexec_ret_73;}
      }
      vmcase(OP_SETI) {
        StkId ra = RA(i);
        int hres;
        int b = GETARG_B(i);
        TValue *rc = RKC(i);
        luaV_fastseti(s2v(ra), b, rc, hres);
        if (hres == HOK)
          luaV_finishfastset(pIp -> L, s2v(ra), rc);
        else {
          TValue key;
          setivalue(&key, b);
          Protect(luaV_finishset(pIp -> L, s2v(ra), &key, rc, hres));
        }
        {int luaG_traceexec_ret_72;IPCALL(luaG_traceexec,ipluaG_traceexec_59,.ret = &luaG_traceexec_ret_72);luaG_traceexec_ret_72;}
      }
      vmcase(OP_SETFIELD) {
        StkId ra = RA(i);
        int hres;
        TValue *rb = KB(i);
        TValue *rc = RKC(i);
        TString *key = tsvalue(rb);  /* key must be a short string */
        luaV_fastset(s2v(ra), key, rc, hres, luaH_psetshortstr);
        if (hres == HOK)
          luaV_finishfastset(pIp -> L, s2v(ra), rc);
        else
          Protect(luaV_finishset(pIp -> L, s2v(ra), rb, rc, hres));
        {int luaG_traceexec_ret_71;IPCALL(luaG_traceexec,ipluaG_traceexec_58,.ret = &luaG_traceexec_ret_71);luaG_traceexec_ret_71;}
      }
      vmcase(OP_NEWTABLE) {
        StkId ra = RA(i);
        unsigned b = cast_uint(GETARG_vB(i));  /* log2(hash size) + 1 */
        unsigned c = cast_uint(GETARG_vC(i));  /* array size */
        Table *t;
        if (b > 0)
          b = 1u << (b - 1);  /* hash size is 2^(b - 1) */
        if (TESTARG_k(i)) {  /* non-zero extra argument? */
          lua_assert(GETARG_Ax(*pc) != 0);
          /* add it to array size */
          c += cast_uint(GETARG_Ax(*pc)) * (MAXARG_vC + 1);
        }
        pc++;  /* skip extra argument */
        pIp -> L->top.p = ra + 1;  /* correct top in case of emergency GC */
        {Table * luaH_new_ret_70;IPCALL(luaH_new,ipluaH_new_0,.ret = luaH_new_ret_70);t = luaH_new_ret_70;}  /* memory allocation */
        sethvalue2s(pIp -> L, ra, t);
        if (b != 0 || c != 0)
          {IPCALL(luaH_resize,ipluaH_resize_0);}  /* idem */
        checkGC(pIp -> L, ra + 1);
        {int luaG_traceexec_ret_69;IPCALL(luaG_traceexec,ipluaG_traceexec_57,.ret = &luaG_traceexec_ret_69);luaG_traceexec_ret_69;}
      }
      vmcase(OP_SELF) {
        StkId ra = RA(i);
        lu_byte tag;
        TValue *rb = vRB(i);
        TValue *rc = KC(i);
        TString *key = tsvalue(rc);  /* key must be a short string */
        setobj2s(pIp -> L, ra + 1, rb);
        luaV_fastget(rb, key, s2v(ra), luaH_getshortstr, tag);
        if (tagisempty(tag))
          {lu_byte luaV_finishget_ret_68;IPCALL(luaV_finishget,ipluaV_finishget_0,.ret = &luaV_finishget_ret_68);}rotect(luaV_finishget(pIp -> L, rb, rc, ra, tag));
        {int luaG_traceexec_ret_67;IPCALL(luaG_traceexec,ipluaG_traceexec_56,.ret = &luaG_traceexec_ret_67);luaG_traceexec_ret_67;}
      }
      vmcase(OP_ADDI) {
        op_arithI(pIp -> L, l_addi, luai_numadd);
        {int luaG_traceexec_ret_66;IPCALL(luaG_traceexec,ipluaG_traceexec_55,.ret = &luaG_traceexec_ret_66);luaG_traceexec_ret_66;}
      }
      vmcase(OP_ADDK) {
        op_arithK(pIp -> L, l_addi, luai_numadd);
        {int luaG_traceexec_ret_65;IPCALL(luaG_traceexec,ipluaG_traceexec_54,.ret = &luaG_traceexec_ret_65);luaG_traceexec_ret_65;}
      }
      vmcase(OP_SUBK) {
        op_arithK(pIp -> L, l_subi, luai_numsub);
        {int luaG_traceexec_ret_64;IPCALL(luaG_traceexec,ipluaG_traceexec_53,.ret = &luaG_traceexec_ret_64);luaG_traceexec_ret_64;}
      }
      vmcase(OP_MULK) {
        op_arithK(pIp -> L, l_muli, luai_nummul);
        {int luaG_traceexec_ret_63;IPCALL(luaG_traceexec,ipluaG_traceexec_52,.ret = &luaG_traceexec_ret_63);luaG_traceexec_ret_63;}
      }
      vmcase(OP_MODK) {
        savestate(pIp -> L, pIp -> ci);  /* in case of division by 0 */
        op_arithK(pIp -> L, luaV_mod, luaV_modf);
        {int luaG_traceexec_ret_62;IPCALL(luaG_traceexec,ipluaG_traceexec_51,.ret = &luaG_traceexec_ret_62);luaG_traceexec_ret_62;}
      }
      vmcase(OP_POWK) {
        op_arithfK(pIp -> L, luai_numpow);
        {int luaG_traceexec_ret_61;IPCALL(luaG_traceexec,ipluaG_traceexec_50,.ret = &luaG_traceexec_ret_61);luaG_traceexec_ret_61;}
      }
      vmcase(OP_DIVK) {
        op_arithfK(pIp -> L, luai_numdiv);
        {int luaG_traceexec_ret_60;IPCALL(luaG_traceexec,ipluaG_traceexec_49,.ret = &luaG_traceexec_ret_60);luaG_traceexec_ret_60;}
      }
      vmcase(OP_IDIVK) {
        savestate(pIp -> L, pIp -> ci);  /* in case of division by 0 */
        op_arithK(pIp -> L, luaV_idiv, luai_numidiv);
        {int luaG_traceexec_ret_59;IPCALL(luaG_traceexec,ipluaG_traceexec_48,.ret = &luaG_traceexec_ret_59);luaG_traceexec_ret_59;}
      }
      vmcase(OP_BANDK) {
        op_bitwiseK(pIp -> L, l_band);
        {int luaG_traceexec_ret_58;IPCALL(luaG_traceexec,ipluaG_traceexec_47,.ret = &luaG_traceexec_ret_58);luaG_traceexec_ret_58;}
      }
      vmcase(OP_BORK) {
        op_bitwiseK(pIp -> L, l_bor);
        {int luaG_traceexec_ret_57;IPCALL(luaG_traceexec,ipluaG_traceexec_46,.ret = &luaG_traceexec_ret_57);luaG_traceexec_ret_57;}
      }
      vmcase(OP_BXORK) {
        op_bitwiseK(pIp -> L, l_bxor);
        {int luaG_traceexec_ret_56;IPCALL(luaG_traceexec,ipluaG_traceexec_45,.ret = &luaG_traceexec_ret_56);luaG_traceexec_ret_56;}
      }
      vmcase(OP_SHRI) {
        StkId ra = RA(i);
        TValue *rb = vRB(i);
        int ic = GETARG_sC(i);
        lua_Integer ib;
        if (tointegerns(rb, &ib)) {
          pc++; {lua_Integer luaV_shiftl_ret_55;IPCALL(luaV_shiftl,ipluaV_shiftl_1,.ret = &luaV_shiftl_ret_55);luaV_shiftl_ret_55sluaV_shiftl_ret_55eluaV_shiftl_ret_55tluaV_shiftl_ret_55iluaV_shiftl_ret_55vluaV_shiftl_ret_55aluaV_shiftl_ret_55lluaV_shiftl_ret_55uluaV_shiftl_ret_55eluaV_shiftl_ret_55(luaV_shiftl_ret_55sluaV_shiftl_ret_552luaV_shiftl_ret_55vluaV_shiftl_ret_55(luaV_shiftl_ret_55rluaV_shiftl_ret_55aluaV_shiftl_ret_55)luaV_shiftl_ret_55,luaV_shiftl_ret_55 luaV_shiftl_ret_55lluaV_shiftl_ret_55uluaV_shiftl_ret_55aluaV_shiftl_ret_55VluaV_shiftl_ret_55_luaV_shiftl_ret_55sluaV_shiftl_ret_55hluaV_shiftl_ret_55iluaV_shiftl_ret_55fluaV_shiftl_ret_55tluaV_shiftl_ret_55lluaV_shiftl_ret_55(luaV_shiftl_ret_55iluaV_shiftl_ret_55bluaV_shiftl_ret_55,luaV_shiftl_ret_55 luaV_shiftl_ret_55-luaV_shiftl_ret_55iluaV_shiftl_ret_55cluaV_shiftl_ret_55)luaV_shiftl_ret_55)luaV_shiftl_ret_55;}
        }
        {int luaG_traceexec_ret_54;IPCALL(luaG_traceexec,ipluaG_traceexec_44,.ret = &luaG_traceexec_ret_54);luaG_traceexec_ret_54;}
      }
      vmcase(OP_SHLI) {
        StkId ra = RA(i);
        TValue *rb = vRB(i);
        int ic = GETARG_sC(i);
        lua_Integer ib;
        if (tointegerns(rb, &ib)) {
          pc++; {lua_Integer luaV_shiftl_ret_53;IPCALL(luaV_shiftl,ipluaV_shiftl_0,.ret = &luaV_shiftl_ret_53);luaV_shiftl_ret_53sluaV_shiftl_ret_53eluaV_shiftl_ret_53tluaV_shiftl_ret_53iluaV_shiftl_ret_53vluaV_shiftl_ret_53aluaV_shiftl_ret_53lluaV_shiftl_ret_53uluaV_shiftl_ret_53eluaV_shiftl_ret_53(luaV_shiftl_ret_53sluaV_shiftl_ret_532luaV_shiftl_ret_53vluaV_shiftl_ret_53(luaV_shiftl_ret_53rluaV_shiftl_ret_53aluaV_shiftl_ret_53)luaV_shiftl_ret_53,luaV_shiftl_ret_53 luaV_shiftl_ret_53lluaV_shiftl_ret_53uluaV_shiftl_ret_53aluaV_shiftl_ret_53VluaV_shiftl_ret_53_luaV_shiftl_ret_53sluaV_shiftl_ret_53hluaV_shiftl_ret_53iluaV_shiftl_ret_53fluaV_shiftl_ret_53tluaV_shiftl_ret_53lluaV_shiftl_ret_53(luaV_shiftl_ret_53iluaV_shiftl_ret_53cluaV_shiftl_ret_53,luaV_shiftl_ret_53 luaV_shiftl_ret_53iluaV_shiftl_ret_53bluaV_shiftl_ret_53)luaV_shiftl_ret_53)luaV_shiftl_ret_53;}
        }
        {int luaG_traceexec_ret_52;IPCALL(luaG_traceexec,ipluaG_traceexec_43,.ret = &luaG_traceexec_ret_52);luaG_traceexec_ret_52;}
      }
      vmcase(OP_ADD) {
        op_arith(pIp -> L, l_addi, luai_numadd);
        {int luaG_traceexec_ret_51;IPCALL(luaG_traceexec,ipluaG_traceexec_42,.ret = &luaG_traceexec_ret_51);luaG_traceexec_ret_51;}
      }
      vmcase(OP_SUB) {
        op_arith(pIp -> L, l_subi, luai_numsub);
        {int luaG_traceexec_ret_50;IPCALL(luaG_traceexec,ipluaG_traceexec_41,.ret = &luaG_traceexec_ret_50);luaG_traceexec_ret_50;}
      }
      vmcase(OP_MUL) {
        op_arith(pIp -> L, l_muli, luai_nummul);
        {int luaG_traceexec_ret_49;IPCALL(luaG_traceexec,ipluaG_traceexec_40,.ret = &luaG_traceexec_ret_49);luaG_traceexec_ret_49;}
      }
      vmcase(OP_MOD) {
        savestate(pIp -> L, pIp -> ci);  /* in case of division by 0 */
        op_arith(pIp -> L, luaV_mod, luaV_modf);
        {int luaG_traceexec_ret_48;IPCALL(luaG_traceexec,ipluaG_traceexec_39,.ret = &luaG_traceexec_ret_48);luaG_traceexec_ret_48;}
      }
      vmcase(OP_POW) {
        op_arithf(pIp -> L, luai_numpow);
        {int luaG_traceexec_ret_47;IPCALL(luaG_traceexec,ipluaG_traceexec_38,.ret = &luaG_traceexec_ret_47);luaG_traceexec_ret_47;}
      }
      vmcase(OP_DIV) {  /* float division (always with floats) */
        op_arithf(pIp -> L, luai_numdiv);
        {int luaG_traceexec_ret_46;IPCALL(luaG_traceexec,ipluaG_traceexec_37,.ret = &luaG_traceexec_ret_46);luaG_traceexec_ret_46;}
      }
      vmcase(OP_IDIV) {  /* floor division */
        savestate(pIp -> L, pIp -> ci);  /* in case of division by 0 */
        op_arith(pIp -> L, luaV_idiv, luai_numidiv);
        {int luaG_traceexec_ret_45;IPCALL(luaG_traceexec,ipluaG_traceexec_36,.ret = &luaG_traceexec_ret_45);luaG_traceexec_ret_45;}
      }
      vmcase(OP_BAND) {
        {int luaV_tointegerns_ret_44;IPCALL(luaV_tointegerns,ipluaV_tointegerns_4,.obj = L,.p = l_band,.ret = &luaV_tointegerns_ret_44);oluaV_tointegerns_ret}44)
        {int luaG_traceexec_ret_43;IPCALL(luaG_traceexec,ipluaG_traceexec_35,.ret = &luaG_traceexec_ret_43);luaG_traceexec_ret_43;}
      }
      vmcase(OP_BOR) {
        {int luaV_tointegerns_ret_42;IPCALL(luaV_tointegerns,ipluaV_tointegerns_3,.obj = L,.p = l_bor,.ret = &luaV_tointegerns_ret_42);oluaV_tointegerns_re}_42)
        {int luaG_traceexec_ret_41;IPCALL(luaG_traceexec,ipluaG_traceexec_34,.ret = &luaG_traceexec_ret_41);luaG_traceexec_ret_41;}
      }
      vmcase(OP_BXOR) {
        {int luaV_tointegerns_ret_40;IPCALL(luaV_tointegerns,ipluaV_tointegerns_2,.obj = L,.p = l_bxor,.ret = &luaV_tointegerns_ret_40);oluaV_tointegerns_ret}40)
        {int luaG_traceexec_ret_39;IPCALL(luaG_traceexec,ipluaG_traceexec_33,.ret = &luaG_traceexec_ret_39);luaG_traceexec_ret_39;}
      }
      vmcase(OP_SHR) {
        {int luaV_tointegerns_ret_38;IPCALL(luaV_tointegerns,ipluaV_tointegerns_1,.obj = L,.p = luaV_shiftr,.ret = &luaV_tointegerns_ret_38);oluaV_tointegerns_ret_38)}
        {int luaG_traceexec_ret_37;IPCALL(luaG_traceexec,ipluaG_traceexec_32,.ret = &luaG_traceexec_ret_37);luaG_traceexec_ret_37;}
      }
      vmcase(OP_SHL) {
        {int luaV_tointegerns_ret_36;IPCALL(luaV_tointegerns,ipluaV_tointegerns_0,.obj = L,.p = luaV_shiftl,.ret = &luaV_tointegerns_ret_36);oluaV_tointegerns_ret_36)}
        {int luaG_traceexec_ret_35;IPCALL(luaG_traceexec,ipluaG_traceexec_31,.ret = &luaG_traceexec_ret_35);luaG_traceexec_ret_35;}
      }
      vmcase(OP_MMBIN) {
        StkId ra = RA(i);
        Instruction pi = *(pc - 2);  /* original arith. expression */
        TValue *rb = vRB(i);
        TMS tm = (TMS)GETARG_C(i);
        StkId result = RA(pi);
        lua_assert(OP_ADD <= GET_OPCODE(pi) && GET_OPCODE(pi) <= OP_SHR);
        Protect(luaT_trybinTM(pIp -> L, s2v(ra), rb, result, tm));
        {int luaG_traceexec_ret_34;IPCALL(luaG_traceexec,ipluaG_traceexec_30,.ret = &luaG_traceexec_ret_34);luaG_traceexec_ret_34;}
      }
      vmcase(OP_MMBINI) {
        StkId ra = RA(i);
        Instruction pi = *(pc - 2);  /* original arith. expression */
        int imm = GETARG_sB(i);
        TMS tm = (TMS)GETARG_C(i);
        int flip = GETARG_k(i);
        StkId result = RA(pi);
        Protect(luaT_trybiniTM(pIp -> L, s2v(ra), imm, flip, result, tm));
        {int luaG_traceexec_ret_33;IPCALL(luaG_traceexec,ipluaG_traceexec_29,.ret = &luaG_traceexec_ret_33);luaG_traceexec_ret_33;}
      }
      vmcase(OP_MMBINK) {
        StkId ra = RA(i);
        Instruction pi = *(pc - 2);  /* original arith. expression */
        TValue *imm = KB(i);
        TMS tm = (TMS)GETARG_C(i);
        int flip = GETARG_k(i);
        StkId result = RA(pi);
        Protect(luaT_trybinassocTM(pIp -> L, s2v(ra), imm, flip, result, tm));
        {int luaG_traceexec_ret_32;IPCALL(luaG_traceexec,ipluaG_traceexec_28,.ret = &luaG_traceexec_ret_32);luaG_traceexec_ret_32;}
      }
      vmcase(OP_UNM) {
        StkId ra = RA(i);
        TValue *rb = vRB(i);
        lua_Number nb;
        if (ttisinteger(rb)) {
          lua_Integer ib = ivalue(rb);
          setivalue(s2v(ra), intop(-, 0, ib));
        }
        else if (tonumberns(rb, nb)) {
          setfltvalue(s2v(ra), luai_numunm(pIp -> L, nb));
        }
        else
          Protect(luaT_trybinTM(pIp -> L, rb, rb, ra, TM_UNM));
        {int luaG_traceexec_ret_31;IPCALL(luaG_traceexec,ipluaG_traceexec_27,.ret = &luaG_traceexec_ret_31);luaG_traceexec_ret_31;}
      }
      vmcase(OP_BNOT) {
        StkId ra = RA(i);
        TValue *rb = vRB(i);
        lua_Integer ib;
        if (tointegerns(rb, &ib)) {
          setivalue(s2v(ra), intop(^, ~l_castS2U(0), ib));
        }
        else
          Protect(luaT_trybinTM(pIp -> L, rb, rb, ra, TM_BNOT));
        {int luaG_traceexec_ret_30;IPCALL(luaG_traceexec,ipluaG_traceexec_26,.ret = &luaG_traceexec_ret_30);luaG_traceexec_ret_30;}
      }
      vmcase(OP_NOT) {
        StkId ra = RA(i);
        TValue *rb = vRB(i);
        if (l_isfalse(rb))
          setbtvalue(s2v(ra));
        else
          setbfvalue(s2v(ra));
        {int luaG_traceexec_ret_29;IPCALL(luaG_traceexec,ipluaG_traceexec_25,.ret = &luaG_traceexec_ret_29);luaG_traceexec_ret_29;}
      }
      vmcase(OP_LEN) {
        StkId ra = RA(i);
        Protect(luaV_objlen(pIp -> L, ra, vRB(i)));
        {int luaG_traceexec_ret_28;IPCALL(luaG_traceexec,ipluaG_traceexec_24,.ret = &luaG_traceexec_ret_28);luaG_traceexec_ret_28;}
      }
      vmcase(OP_CONCAT) {
        StkId ra = RA(i);
        int n = GETARG_B(i);  /* number of elements to concatenate */
        pIp -> L->top.p = ra + n;  /* mark the end of concat operands */
        ProtectNT(luaV_concat(pIp -> L, n));
        {IPCALL(luaC_step,ipluaC_step_1);} /* 'luaV_concat' ensures correct top */
        {int luaG_traceexec_ret_27;IPCALL(luaG_traceexec,ipluaG_traceexec_23,.ret = &luaG_traceexec_ret_27);luaG_traceexec_ret_27;}
      }
      vmcase(OP_CLOSE) {
        StkId ra = RA(i);
        lua_assert(!GETARG_B(i));  /* 'close must be alive */
        Protect(luaF_close(pIp -> L, ra, LUA_OK, 1));
        {int luaG_traceexec_ret_26;IPCALL(luaG_traceexec,ipluaG_traceexec_22,.ret = &luaG_traceexec_ret_26);luaG_traceexec_ret_26;}
      }
      vmcase(OP_TBC) {
        StkId ra = RA(i);
        /* create new to-be-closed upvalue */
        halfProtect(luaF_newtbcupval(pIp -> L, ra));
        {int luaG_traceexec_ret_25;IPCALL(luaG_traceexec,ipluaG_traceexec_21,.ret = &luaG_traceexec_ret_25);luaG_traceexec_ret_25;}
      }
      vmcase(OP_JMP) {
        dojump(pIp -> ci, i, 0);
        {int luaG_traceexec_ret_24;IPCALL(luaG_traceexec,ipluaG_traceexec_20,.ret = &luaG_traceexec_ret_24);luaG_traceexec_ret_24;}
      }
      vmcase(OP_EQ) {
        StkId ra = RA(i);
        int cond;
        TValue *rb = vRB(i);
        Protect(cond = luaV_equalobj(pIp -> L, s2v(ra), rb));
        docondjump();
        {int luaG_traceexec_ret_23;IPCALL(luaG_traceexec,ipluaG_traceexec_19,.ret = &luaG_traceexec_ret_23);luaG_traceexec_ret_23;}
      }
      vmcase(OP_LT) {
        op_order(pIp -> L, l_lti, LTnum, lessthanothers);
        {int luaG_traceexec_ret_22;IPCALL(luaG_traceexec,ipluaG_traceexec_18,.ret = &luaG_traceexec_ret_22);luaG_traceexec_ret_22;}
      }
      vmcase(OP_LE) {
        op_order(pIp -> L, l_lei, LEnum, lessequalothers);
        {int luaG_traceexec_ret_21;IPCALL(luaG_traceexec,ipluaG_traceexec_17,.ret = &luaG_traceexec_ret_21);luaG_traceexec_ret_21;}
      }
      vmcase(OP_EQK) {
        StkId ra = RA(i);
        TValue *rb = KB(i);
        /* basic types do not use '__eq'; we can use raw equality */
        int cond = luaV_rawequalobj(s2v(ra), rb);
        docondjump();
        {int luaG_traceexec_ret_20;IPCALL(luaG_traceexec,ipluaG_traceexec_16,.ret = &luaG_traceexec_ret_20);luaG_traceexec_ret_20;}
      }
      vmcase(OP_EQI) {
        StkId ra = RA(i);
        int cond;
        int im = GETARG_sB(i);
        if (ttisinteger(s2v(ra)))
          cond = (ivalue(s2v(ra)) == im);
        else if (ttisfloat(s2v(ra)))
          cond = luai_numeq(fltvalue(s2v(ra)), cast_num(im));
        else
          cond = 0;  /* other types cannot be equal to a number */
        docondjump();
        {int luaG_traceexec_ret_19;IPCALL(luaG_traceexec,ipluaG_traceexec_15,.ret = &luaG_traceexec_ret_19);luaG_traceexec_ret_19;}
      }
      vmcase(OP_LTI) {
        op_orderI(pIp -> L, l_lti, luai_numlt, 0, TM_LT);
        {int luaG_traceexec_ret_18;IPCALL(luaG_traceexec,ipluaG_traceexec_14,.ret = &luaG_traceexec_ret_18);luaG_traceexec_ret_18;}
      }
      vmcase(OP_LEI) {
        op_orderI(pIp -> L, l_lei, luai_numle, 0, TM_LE);
        {int luaG_traceexec_ret_17;IPCALL(luaG_traceexec,ipluaG_traceexec_13,.ret = &luaG_traceexec_ret_17);luaG_traceexec_ret_17;}
      }
      vmcase(OP_GTI) {
        op_orderI(pIp -> L, l_gti, luai_numgt, 1, TM_LT);
        {int luaG_traceexec_ret_16;IPCALL(luaG_traceexec,ipluaG_traceexec_12,.ret = &luaG_traceexec_ret_16);luaG_traceexec_ret_16;}
      }
      vmcase(OP_GEI) {
        op_orderI(pIp -> L, l_gei, luai_numge, 1, TM_LE);
        {int luaG_traceexec_ret_15;IPCALL(luaG_traceexec,ipluaG_traceexec_11,.ret = &luaG_traceexec_ret_15);luaG_traceexec_ret_15;}
      }
      vmcase(OP_TEST) {
        StkId ra = RA(i);
        int cond = !l_isfalse(s2v(ra));
        docondjump();
        {int luaG_traceexec_ret_14;IPCALL(luaG_traceexec,ipluaG_traceexec_10,.ret = &luaG_traceexec_ret_14);luaG_traceexec_ret_14;}
      }
      vmcase(OP_TESTSET) {
        StkId ra = RA(i);
        TValue *rb = vRB(i);
        if (l_isfalse(rb) == GETARG_k(i))
          pc++;
        else {
          setobj2s(pIp -> L, ra, rb);
          donextjump(pIp -> ci);
        }
        {int luaG_traceexec_ret_13;IPCALL(luaG_traceexec,ipluaG_traceexec_9,.ret = &luaG_traceexec_ret_13);luaG_traceexec_ret_13;}
      }
      vmcase(OP_CALL) {
        StkId ra = RA(i);
        CallInfo *newci;
        int b = GETARG_B(i);
        int nresults = GETARG_C(i) - 1;
        if (b != 0)  /* fixed number of arguments? */
          pIp -> L->top.p = ra + b;  /* top signals number of arguments */
        /* else previous instruction set top */
        savepc(pIp -> L);  /* in case of errors */
        {CallInfo * luaD_precall_ret_12;IPCALL(luaD_precall,ipluaD_precall_0,.ret = luaD_precall_ret_12);if ((newci = (luaD_precall_ret_12) == NULL)
          updatetrap(pIp -> ci);  /* C call; nothing else to be done */
        else {  /* Lua call: run function in this same C frame */
          pIp -> ci = newci;
          goto startfunc;
        }}
        {int luaG_traceexec_ret_11;IPCALL(luaG_traceexec,ipluaG_traceexec_8,.ret = &luaG_traceexec_ret_11);luaG_traceexec_ret_11;}
      }
      vmcase(OP_TAILCALL) {
        StkId ra = RA(i);
        int b = GETARG_B(i);  /* number of arguments + 1 (function) */
        int n;  /* number of results when calling a C function */
        int nparams1 = GETARG_C(i);
        /* delta is virtual 'func' - real 'func' (vararg functions) */
        int delta = (nparams1) ? pIp -> ci->u.l.nextraargs + nparams1 : 0;
        if (b != 0)
          pIp -> L->top.p = ra + b;
        else  /* previous instruction set top */
          b = cast_int(pIp -> L->top.p - ra);
        savepc(pIp -> ci);  /* several calls here can raise errors */
        if (TESTARG_k(i)) {
          {IPCALL(luaF_closeupval,ipluaF_closeupval_0);}  /* close upvalues from current call */
          lua_assert(pIp -> L->tbclist.p < base);  /* no pending tbc variables */
          lua_assert(base == pIp -> ci->func.p + 1);
        }
        {int luaD_pretailcall_ret_10;IPCALL(luaD_pretailcall,ipluaD_pretailcall_0,.ret = &luaD_pretailcall_ret_10);if ((n = (luaD_pretailcall_ret_10) < 0)  /* Lua function? */
          goto startfunc;  /* execute the callee */
        else {  /* C function? */
          pIp -> ci->func.p -= delta;  /* restore 'func' (if vararg) */
          {IPCALL(luaD_poscall,ipluaD_poscall_3);}  /* finish caller */
          updatetrap(pIp -> ci);  /* 'luaD_poscall' can change hooks */
          goto ret;  /* caller returns after the tail call */
        }}
      }
      vmcase(OP_RETURN) {
        StkId ra = RA(i);
        int n = GETARG_B(i) - 1;  /* number of results */
        int nparams1 = GETARG_C(i);
        if (n < 0)  /* not fixed? */
          n = cast_int(pIp -> L->top.p - ra);  /* get what is available */
        savepc(pIp -> ci);
        if (TESTARG_k(i)) {  /* may there be open upvalues? */
          pIp -> ci->u2.nres = n;  /* save number of returns */
          if (pIp -> L->top.p < pIp -> ci->top.p)
            pIp -> L->top.p = pIp -> ci->top.p;
          {StkId luaF_close_ret_9;IPCALL(luaF_close,ipluaF_close_0,.ret = &luaF_close_ret_9);}
          updatetrap(pIp -> ci);
          updatestack(pIp -> ci);
        }
        if (nparams1)  /* vararg function? */
          pIp -> ci->func.p -= pIp -> ci->u.l.nextraargs + nparams1;
        pIp -> L->top.p = ra + n;  /* set call for 'luaD_poscall' */
        {IPCALL(luaD_poscall,ipluaD_poscall_2);}
        updatetrap(pIp -> ci);  /* 'luaD_poscall' can change hooks */
        goto ret;
      }
      vmcase(OP_RETURN0) {
        if (l_unlikely(pIp -> L->hookmask)) {
          StkId ra = RA(i);
          pIp -> L->top.p = ra;
          savepc(pIp -> ci);
          {IPCALL(luaD_poscall,ipluaD_poscall_1);}  /* no hurry... */
          trap = 1;
        }
        else {  /* do the 'poscall' here */
          int nres = get_nresults(pIp -> ci->callstatus);
          pIp -> L->pIp -> ci = pIp -> ci->previous;  /* back to caller */
          pIp -> L->top.p = base - 1;
          for (; l_unlikely(nres > 0); nres--)
            setnilvalue(s2v(pIp -> L->top.p++));  /* all results are nil */
        }
        goto ret;
      }
      vmcase(OP_RETURN1) {
        if (l_unlikely(pIp -> L->hookmask)) {
          StkId ra = RA(i);
          pIp -> L->top.p = ra + 1;
          savepc(pIp -> ci);
          {IPCALL(luaD_poscall,ipluaD_poscall_0);}  /* no hurry... */
          trap = 1;
        }
        else {  /* do the 'poscall' here */
          int nres = get_nresults(pIp -> ci->callstatus);
          pIp -> L->pIp -> ci = pIp -> ci->previous;  /* back to caller */
          if (nres == 0)
            pIp -> L->top.p = base - 1;  /* asked for no results */
          else {
            StkId ra = RA(i);
            setobjs2s(pIp -> L, base - 1, ra);  /* at least this result */
            pIp -> L->top.p = base;
            for (; l_unlikely(nres > 1); nres--)
              setnilvalue(s2v(pIp -> L->top.p++));  /* complete missing results */
          }
        }
       ret:  /* return from a Lua function */
        if (pIp -> ci->callstatus & CIST_FRESH)
          return;  /* end this frame */
        else {
          pIp -> ci = pIp -> ci->previous;
          goto returning;  /* continue running caller in this frame */
        }
      }
      vmcase(OP_FORLOOP) {
        StkId ra = RA(i);
        if (ttisinteger(s2v(ra + 1))) {  /* integer loop? */
          lua_Unsigned count = l_castS2U(ivalue(s2v(ra)));
          if (count > 0) {  /* still more iterations? */
            lua_Integer step = ivalue(s2v(ra + 1));
            lua_Integer idx = ivalue(s2v(ra + 2));  /* control variable */
            chgivalue(s2v(ra), l_castU2S(count - 1));  /* update counter */
            idx = intop(+, idx, step);  /* add step to index */
            chgivalue(s2v(ra + 2), idx);  /* update control variable */
            pc -= GETARG_Bx(i);  /* jump back */
          }
        }
        else if (floatforloop(ra))  /* float loop */
          pc -= GETARG_Bx(i);  /* jump back */
        updatetrap(pIp -> ci);  /* allows a signal to break the loop */
        {int luaG_traceexec_ret_8;IPCALL(luaG_traceexec,ipluaG_traceexec_7,.ret = &luaG_traceexec_ret_8);luaG_traceexec_ret_8;}
      }
      vmcase(OP_FORPREP) {
        StkId ra = RA(i);
        savestate(pIp -> L, pIp -> ci);  /* in case of errors */
        {int forprep_ret_7;IPCALL(forprep,ipforprep_0,.L = pIp->L,.ra = ra,.ret = &forprep_ret_7);if ((forprep_ret_7)
          pc += GETARG_Bx(i) + 1}  /* skip the loop */
        {int luaG_traceexec_ret_6;IPCALL(luaG_traceexec,ipluaG_traceexec_6,.ret = &luaG_traceexec_ret_6);luaG_traceexec_ret_6;}
      }
      vmcase(OP_TFORPREP) {
       /* before: 'ra' has the iterator function, 'ra + 1' has the state,
          'ra + 2' has the initial value for the control variable, and
          'ra + 3' has the closing variable. This opcode then swaps the
          control and the closing variables and marks the closing variable
          as to-be-closed.
       */
       StkId ra = RA(i);
       TValue temp;  /* to swap control and closing variables */
       setobj(pIp -> L, &temp, s2v(ra + 3));
       setobjs2s(pIp -> L, ra + 3, ra + 2);
       setobj2s(pIp -> L, ra + 2, &temp);
        /* create to-be-closed upvalue (if closing var. is not nil) */
        halfProtect(luaF_newtbcupval(pIp -> L, ra + 2));
        pc += GETARG_Bx(i);  /* go to end of the loop */
        i = *(pc++);  /* fetch next instruction */
        lua_assert(GET_OPCODE(i) == OP_TFORCALL && ra == RA(i));
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
        StkId ra = RA(i);
        setobjs2s(pIp -> L, ra + 5, ra + 3);  /* copy the control variable */
        setobjs2s(pIp -> L, ra + 4, ra + 1);  /* copy state */
        setobjs2s(pIp -> L, ra + 3, ra);  /* copy function */
        pIp -> L->top.p = ra + 3 + 3;
        {IPCALL(luaD_call,ipluaD_call_0);ProtectNT(luaD_call(pIp->L, ra + 3, GETARG_C(i)));}  /* do the call */
        updatestack(pIp -> ci);  /* stack may have changed */
        i = *(pc++);  /* go to next instruction */
        lua_assert(GET_OPCODE(i) == OP_TFORLOOP && ra == RA(i));
        goto l_tforloop;
      }}
      vmcase(OP_TFORLOOP) {
       l_tforloop: {
        StkId ra = RA(i);
        if (!ttisnil(s2v(ra + 3)))  /* continue loop? */
          pc -= GETARG_Bx(i);  /* jump back */
        {int luaG_traceexec_ret_5;IPCALL(luaG_traceexec,ipluaG_traceexec_5,.ret = &luaG_traceexec_ret_5);luaG_traceexec_ret_5;}
      }}
      vmcase(OP_SETLIST) {
        StkId ra = RA(i);
        unsigned n = cast_uint(GETARG_vB(i));
        unsigned int last = cast_uint(GETARG_vC(i));
        Table *h = hvalue(s2v(ra));
        if (n == 0)
          n = cast_uint(pIp -> L->top.p - ra) - 1;  /* get up to the top */
        else
          pIp -> L->top.p = pIp -> ci->top.p;  /* correct top in case of emergency GC */
        last += n;
        if (TESTARG_k(i)) {
          last += cast_uint(GETARG_Ax(*pc)) * (MAXARG_vC + 1);
          pc++;
        }
        /* when 'n' is known, table should have proper size */
        if (last > h->asize) {  /* needs more space? */
          /* fixed-size sets should have space preallocated */
          lua_assert(GETARG_vB(i) == 0);
          {IPCALL(luaH_resizearray,ipluaH_resizearray_0);}  /* preallocate it at once */
        }
        for (; n > 0; n--) {
          TValue *val = s2v(ra + n);
          obj2arr(h, last - 1, val);
          last--;
          luaC_barrierback(pIp -> L, obj2gco(h), val);
        }
        {int luaG_traceexec_ret_4;IPCALL(luaG_traceexec,ipluaG_traceexec_4,.ret = &luaG_traceexec_ret_4);luaG_traceexec_ret_4;}
      }
      vmcase(OP_CLOSURE) {
        StkId ra = RA(i);
        Proto *p = cl->p->p[GETARG_Bx(i)];
        halfProtect(pushclosure(pIp -> L, p, cl->upvals, base, ra));
        {IPCALL(luaC_step,ipluaC_step_0);}
        {int luaG_traceexec_ret_3;IPCALL(luaG_traceexec,ipluaG_traceexec_3,.ret = &luaG_traceexec_ret_3);luaG_traceexec_ret_3;}
      }
      vmcase(OP_VARARG) {
        StkId ra = RA(i);
        int n = GETARG_C(i) - 1;  /* required results */
        Protect(luaT_getvarargs(pIp -> L, pIp -> ci, ra, n));
        {int luaG_traceexec_ret_2;IPCALL(luaG_traceexec,ipluaG_traceexec_2,.ret = &luaG_traceexec_ret_2);luaG_traceexec_ret_2;}
      }
      vmcase(OP_VARARGPREP) {
        ProtectNT(luaT_adjustvarargs(pIp -> L, GETARG_A(i), pIp -> ci, cl->p));
        if (l_unlikely(trap)) {  /* previous "Protect" updated trap */
          {IPCALL(luaD_hookcall,ipluaD_hookcall_0);}
          pIp -> L->oldpc = 1;  /* next opcode will be seen as a "new" line */
        }
        updatebase(pIp -> ci);  /* function has new base after adjustment */
        {int luaG_traceexec_ret_1;IPCALL(luaG_traceexec,ipluaG_traceexec_1,.ret = &luaG_traceexec_ret_1);luaG_traceexec_ret_1;}
      }
      vmcase(OP_EXTRAARG) {
        lua_assert(0);
        {int luaG_traceexec_ret_0;IPCALL(luaG_traceexec,ipluaG_traceexec_0,.ret = &luaG_traceexec_ret_0);luaG_traceexec_ret_0;}
      }
    }
  }
}