#include "rethook.h"
void rethookFun(void *p) 
{
    rethook *pIp = (rethook*)p;
  if ((pIp->L)->hookmask & LUA_MASKRET) {  /* is return hook on? */
    StkId firstres = (pIp->L)->top.p - (pIp->nres);  /* index of first result */
    int delta = 0;  /* correction for vararg functions */
    int ftransfer;
    {if (isLua(pIp->ci)) {
      Proto p;{p = ci_func(pIp->ci)->p;}
      if (p->flag & PF_ISVARARG)
        delta = (pIp->ci)->u.l.nextraargs + p->numparams + 1;
    }}
    (pIp->ci)->func.p += delta;  /* if vararg, back to virtual 'func' */
    {ftransfer = cast_int(firstres - pIp->ci->func.p);}
    {IPCALL(luaD_hook,ipluaD_hook_0,.L = pIp->L,.event = LUA_HOOKRET,.line = -1,.ftransfer = ftransfer,.ntransfer = pIp->nres);}  /* call it */
    (pIp->ci)->func.p -= delta;
  }
  {if (isLua(pIp->ci = pIp->ci->previous))
    {pIp->L->oldpc = pcRel(pIp->ci->u.l.savedpc, ci_func(pIp->ci)->p);}}  /* set 'oldpc' */
}