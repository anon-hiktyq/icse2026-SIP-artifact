#include "luaG_traceexec.h"
void luaG_traceexecFun(void *p) 
{
    luaG_traceexec *pIp = (luaG_traceexec*)p;
  CallInfo *ci = (pIp->L)->ci;
  lu_byte mask;{mask = cast_byte(pIp->L->hookmask);}
  const Proto p;{p = ci_func(ci)->p;}
  int counthook;
  if (!(mask & (LUA_MASKLINE | LUA_MASKCOUNT))) {  /* no hooks? */
    ci->u.l.trap = 0;  /* don't need to stop again */
    *(pIp->ret) =  0;  /* turn off 'trap' */
  }
  (pIp->pc)++;  /* reference is always next instruction */
  ci->u.l.savedpc = (pIp->pc);  /* save 'pc' */
  counthook = (mask & LUA_MASKCOUNT) && (--(pIp->L)->hookcount == 0);
  if (counthook)
    {resethookcount(pIp->L);}  /* reset count */
  else if (!(mask & LUA_MASKLINE))
    *(pIp->ret) =  1;  /* no line hook and count != 0; nothing to be done now */
  if (ci->callstatus & CIST_HOOKYIELD) {  /* hook yielded last time? */
    ci->callstatus &= ~CIST_HOOKYIELD;  /* erase mark */
    *(pIp->ret) =  1;  /* do not call hook again (VM yielded, so it did not move) */
  }
  {int luaP_isIT_ret_0;IPCALL(luaP_isIT,ipluaP_isIT_0,.ret = &luaP_isIT_ret_0);if (!luaP_isIT_ret_0)  /* top not being used? */
    (pIp->L)->top.p = ci->top.p; } /* correct top */
  if (counthook)
    {IPCALL(luaD_hook,ipluaD_hook_0);}  /* call count hook */
  if (mask & LUA_MASKLINE) {
    /* 'L->oldpc' may be invalid; use zero in this case */
    int oldpc = ((pIp->L)->oldpc < p->sizecode) ? (pIp->L)->oldpc : 0;
    int npci;{npci = pcRel(pIp->pc, p);}
    {int changedline_ret_0;IPCALL(changedline,ipchangedline_0,.p = p,.oldpc = oldpc,.newpc = npci,.ret = &changedline_ret_0);if (npci <= oldpc ||  /* call hook when jump back (loop), */
        changedline_ret_0) {  /* or when enter new line */
      int newline;{int luaG_getfuncline_ret_0; IPCALL(luaG_getfuncline,ipluaG_getfuncline_0,.f = p,.pc = npci,.ret = &luaG_getfuncline_ret_0);newline = luaG_getfuncline_ret_0;}
      {IPCALL(luaD_hook,ipluaD_hook_1);}  /* call line hook */
    }}
    (pIp->L)->oldpc = npci;  /* 'pc' of last call to line hook */
  }
  if ((pIp->L)->status == LUA_YIELD) {  /* did hook yield? */
    if (counthook)
      (pIp->L)->hookcount = 1;  /* undo decrement to zero */
    ci->callstatus |= CIST_HOOKYIELD;  /* mark that it yielded */
    {IPCALL(luaD_throw,ipluaD_throw_0);}
  }
  *(pIp->ret) =  1;  /* keep 'trap' on */
}