#include "collectvalidlines.h"
void collectvalidlinesFun(void *p) 
{
    collectvalidlines *pIp = (collectvalidlines*)p;
  {if (!LuaClosure(pIp->f)) {
    {setnilvalue(s2v(pIp->L->top.p));}
    {api_incr_top(pIp->L);}
  }
  else {
    const Proto *p = (pIp->f)->l.p;
    int currentline = p->linedefined;
    Table t;{Table * luaH_new_ret_0; IPCALL(luaH_new,ipluaH_new_0,.ret = luaH_new_ret_0);t = luaH_new_ret_0;}  /* new table to store active lines */
    {sethvalue2s(pIp->L, pIp->L->top.p, t);}  /* push it on stack */
    {api_incr_top(pIp->L);}
    if (p->lineinfo != NULL) {  /* proto with debug information? */
      int i;
      TValue v;
      {setbtvalue(&v);}  /* boolean 'true' to be the value of all indices */
      if (!(p->flag & PF_ISVARARG))  /* regular function? */
        i = 0;  /* consider all instructions */
      else {  /* vararg function */
        {lua_assert(GET_OPCODE(p->code[0]) == OP_VARARGPREP);}
        {int nextline_ret_0;IPCALL(nextline,ipnextline_0,.p = p,.currentline = currentline,.pc = 0,.ret = &nextline_ret_0);currentline = nextline_ret_0;}
        i = 1;  /* skip first instruction (OP_VARARGPREP) */
      }
      for (; i < p->sizelineinfo; i++) {  /* for each instruction */
        {int nextline_ret_1;IPCALL(nextline,ipnextline_1,.p = p,.currentline = currentline,.pc = i,.ret = &nextline_ret_1);currentline = nextline_ret_1;}  /* get its line */
        {IPCALL(luaH_setint,ipluaH_setint_0);}  /* table[line] = true */
      }
    }
  }}
}