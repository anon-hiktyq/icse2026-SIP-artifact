#include "luaF_closeupval.h"
void luaF_closeupvalFun(void *p) 
{
    luaF_closeupval *pIp = (luaF_closeupval*)p;
  UpVal *uv;
  StkId upl;  /* stack index pointed by 'uv' */
  while ((uv = (pIp->L)->openupval) != NULL && (upl = uplevel(uv)) >= (pIp->level)) {
    TValue *slot = &uv->u.value;  /* new position for value */
    {lua_assert(uplevel(uv) < pIp->L->top.p);}
    {IPCALL(luaF_unlinkupval,ipluaF_unlinkupval_0,.uv = uv);}  /* remove upvalue from 'openupval' list */
    {setobj(pIp->L, slot, uv->v.p);}  /* move value to upvalue slot */
    uv->v.p = slot;  /* now current value lives here */
    {if (!iswhite(uv)) {  /* neither white nor dead? */
      {nw2black(uv);}  /* closed upvalues cannot be gray */
      {luaC_barrier(pIp->L, uv, slot);}
    }}
  }
}