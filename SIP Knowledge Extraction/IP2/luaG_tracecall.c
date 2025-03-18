#include "luaG_tracecall.h"
void luaG_tracecallFun(void *p) 
{
    luaG_tracecall *pIp = (luaG_tracecall*)p;
  CallInfo *ci = pIp -> L->ci;
  Proto *p = ci_func(ci)->p;
  ci->u.l.trap = 1;  /* ensure hooks will be checked */
  if (ci->u.l.savedpc == p->code) {  /* first instruction (not resuming)? */
    if (p->flag & PF_ISVARARG)
      *(pIp -> ret) = 0; /* hooks will start at VARARGPREP instruction */
    else if (!(ci->callstatus & CIST_HOOKYIELD))  /* not yielded? */
      {IPCALL(luaD_hookcall,ipluaD_hookcall_0);}  /* check 'call' hook */
  }
  *(pIp -> ret) = 1; /* keep 'trap' on */
}