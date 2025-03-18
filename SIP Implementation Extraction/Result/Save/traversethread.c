#include "traversethread.h"
void traversethreadFun(void *p) 
{
    traversethread *pIp = (traversethread*)p;
  UpVal *uv;
  StkId o = pIp -> th->stack.p;
  if (isold(pIp -> th) || pIp -> g->gcstate == GCSpropagate)
    linkgclist(pIp -> th, pIp -> g->grayagain);  /* insert into 'grayagain' list */
  if (o == NULL)
    *(pIp -> ret) = 0; /* stack not completely built yet */
  lua_assert(pIp -> g->gcstate == GCSatomic ||
             pIp -> th->openupval == NULL || isintwups(pIp -> th));
  for (; o < pIp -> th->top.p; o++)  /* mark live elements in the stack */
    {IPCALL(reallymarkobject,ipreallymarkobject_0,.pIp->g = pIp->pIp->g,.o = s2v(o));}
  for (uv = pIp -> th->openupval; uv != NULL; uv = uv->u.open.next)
    markobject(pIp -> g, uv);  /* open upvalues cannot be collected */
  if (pIp -> g->gcstate == GCSatomic) {  /* final traversal? */
    if (!pIp -> g->gcemergency)
      {IPCALL(luaD_shrinkstack,ipluaD_shrinkstack_0);} /* do not change stack in emergency cycle */
    for (o = pIp -> th->top.p; o < pIp -> th->stack_last.p + EXTRA_STACK; o++)
      setnilvalue(s2v(o));  /* clear dead stack slice */
    /* 'remarkupvals' may have removed thread from 'twups' list */
    if (!isintwups(pIp -> th) && pIp -> th->openupval != NULL) {
      pIp -> th->twups = pIp -> g->twups;  /* link it back to the list */
      pIp -> g->twups = pIp -> th;
    }
  }
  *(pIp -> ret) = 1 + (th->top.p - th->stack.p);
}