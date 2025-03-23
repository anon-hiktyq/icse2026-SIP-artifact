#include "correctstack.h"
void correctstackFun(void *p) 
{
    correctstack *pIp = (correctstack*)p;
  CallInfo *ci;
  UpVal *up;
  StkId newstack = (pIp->L)->stack.p;
  if ((pIp->oldstack) == newstack)
    return;
  (pIp->L)->top.p = (pIp->L)->top.p - (pIp->oldstack) + newstack;
  (pIp->L)->tbclist.p = (pIp->L)->tbclist.p - (pIp->oldstack) + newstack;
  for (up = (pIp->L)->openupval; up != NULL; up = up->u.open.next)
    {up->v.p = s2v(uplevel(up) - pIp->oldstack + newstack);}
  for (ci = (pIp->L)->ci; ci != NULL; ci = ci->previous) {
    ci->top.p = ci->top.p - (pIp->oldstack) + newstack;
    ci->func.p = ci->func.p - (pIp->oldstack) + newstack;
    {if (isLua(ci))
      ci->u.l.trap = 1; } /* signal to update 'trap' in 'luaV_execute' */
  }
}