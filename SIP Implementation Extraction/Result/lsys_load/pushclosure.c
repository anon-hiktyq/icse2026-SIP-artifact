#include "pushclosure.h"
void pushclosureFun(void *p) 
{
    pushclosure *pIp = (pushclosure*)p;
  int nup = (pIp->p)->sizeupvalues;
  Upvaldesc *uv = (pIp->p)->upvalues;
  int i;
  LClosure ncl;{LClosure * luaF_newLclosure_ret_0; IPCALL(luaF_newLclosure,ipluaF_newLclosure_0,.ret = luaF_newLclosure_ret_0);ncl = luaF_newLclosure_ret_0;}
  ncl->p = (pIp->p);
  {setclLvalue2s(pIp->L, pIp->ra, ncl);}  /* anchor new closure in stack */
  for (i = 0; i < nup; i++) {  /* fill in its upvalues */
    if (uv[i].instack)  /* upvalue refers to local variable? */
      {UpVal * luaF_findupval_ret_0;IPCALL(luaF_findupval,ipluaF_findupval_0,.ret = luaF_findupval_ret_0);ncl->upvals[i] = luaF_findupval_ret_0;}
    else  /* get upvalue from enclosing function */
      ncl->upvals[i] = (pIp->encup)[uv[i].idx];
    {luaC_objbarrier(pIp->L, ncl, ncl->upvals[i]);}
  }
}