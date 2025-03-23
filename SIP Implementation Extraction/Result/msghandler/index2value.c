#include "index2value.h"
void index2valueFun(void *p) 
{
    index2value *pIp = (index2value*)p;
  CallInfo *ci = (pIp->L)->ci;
  if ((pIp->idx) > 0) {
    StkId o = ci->func.p + (pIp->idx);
    {api_check(pIp->L, pIp->idx <= ci->top.p - (ci->func.p + 1), "unacceptable index");}
    if (o >= (pIp->L)->top.p) pIp->ret =  &G(L)->nilvalue;
    else pIp->ret =  s2v(o);
  }
  else {if (!ispseudo(pIp->idx)) {  /* negative index */
    {api_check(pIp->L, pIp->idx != 0 && -pIp->idx <= pIp->L->top.p - (ci->func.p + 1),
                 "invalid index");}
    pIp->ret =  s2v(L->top.p + idx);
  }
  else if ((pIp->idx) == LUA_REGISTRYINDEX)
    pIp->ret =  &G(L)->l_registry;
  else {  /* upvalues */
    (pIp->idx) = LUA_REGISTRYINDEX - (pIp->idx);
    {api_check(pIp->L, pIp->idx <= MAXUPVAL + 1, "upvalue index too large");}
    {if (ttisCclosure(s2v(ci->func.p))) {  /* C closure? */
      CClosure func;{func = clCvalue(s2v(ci->func.p));}
      pIp->ret =  (idx <= func->nupvalues) ? &func->upvalue[idx-1]
                                      : &G(L)->nilvalue;
    }
    else {  /* light C function or Lua function (through a hook)?) */
      {api_check(pIp->L, ttislcf(s2v(ci->func.p)), "caller not a C function");}
      pIp->ret =  &G(L)->nilvalue;  /* no upvalues */
    }}
  }}
}