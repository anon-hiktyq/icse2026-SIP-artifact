#include "collectvalidlines.h"
void collectvalidlinesFun(void *p) 
{
    collectvalidlines *pIp = (collectvalidlines*)p;
  if (!LuaClosure(pIp -> f)) {
    setnilvalue(s2v(pIp -> L->top.p));
    api_incr_top(pIp -> L);
  }
  else {
    const Proto *p = pIp -> f->l.p;
    int currentline = p->linedefined;
    Table *t = luaH_new(pIp -> L);  /* new table to store active lines */
    sethvalue2s(pIp -> L, pIp -> L->top.p, t);  /* push it on stack */
    api_incr_top(pIp -> L);
    if (p->lineinfo != NULL) {  /* proto with debug information? */
      int i;
      TValue v;
      setbtvalue(&v);  /* boolean 'true' to be the value of all indices */
      if (!(p->flag & PF_ISVARARG))  /* regular function? */
        i = 0;  /* consider all instructions */
      else {  /* vararg function */
        lua_assert(GET_OPCODE(p->code[0]) == OP_VARARGPREP);
        currentline = nextline(p, currentline, 0);
        i = 1;  /* skip first instruction (OP_VARARGPREP) */
      }
      for (; i < p->sizelineinfo; i++) {  /* for each instruction */
        currentline = nextline(p, currentline, i);  /* get its line */
        luaH_setint(pIp -> L, t, currentline, &v);  /* table[line] = true */
      }
    }
  }
}