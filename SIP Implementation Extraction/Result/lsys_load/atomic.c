#include "atomic.h"
void atomicFun(void *p) 
{
    atomic *pIp = (atomic*)p;
  global_State g;{g = G(pIp->L);}
  GCObject *origweak, *origall;
  GCObject *grayagain = g->grayagain;  /* save original list */
  g->grayagain = NULL;
  {lua_assert(g->ephemeron == NULL && g->weak == NULL);}
  {lua_assert(!iswhite(mainthread(g)));}
  g->gcstate = GCSatomic;
  {markobject(g, pIp->L);}  /* mark running thread */
  /* registry and global metatables may be changed by API */
  {markvalue(g, &g->l_registry);}
  {IPCALL(markmt,ipmarkmt_0,.g = g);}  /* mark global metatables */
  {IPCALL(propagateall,ippropagateall_1,.g = g);}  /* empties 'gray' list */
  /* remark occasional upvalues of (maybe) dead threads */
  {IPCALL(remarkupvals,ipremarkupvals_0,.g = g);}
  {IPCALL(propagateall,ippropagateall_2,.g = g);}  /* propagate changes */
  g->gray = grayagain;
  {IPCALL(propagateall,ippropagateall_0,.g = g);}  /* traverse 'grayagain' list */
  {IPCALL(convergeephemerons,ipconvergeephemerons_1,.g = g);}
  /* at this point, all strongly accessible objects are marked. */
  /* Clear values from weak tables, before checking finalizers */
  {IPCALL(clearbyvalues,ipclearbyvalues_0,.g = g,.l = g->weak,.f = NULL);}
  {IPCALL(clearbyvalues,ipclearbyvalues_1,.g = g,.l = g->allweak,.f = NULL);}
  origweak = g->weak; origall = g->allweak;
  {IPCALL(separatetobefnz,ipseparatetobefnz_0,.g = g,.all = 0);}  /* separate objects to be finalized */
  {IPCALL(markbeingfnz,ipmarkbeingfnz_0,.g = g);}  /* mark objects that will be finalized */
  {IPCALL(propagateall,ippropagateall_3,.g = g);}  /* remark, to propagate 'resurrection' */
  {IPCALL(convergeephemerons,ipconvergeephemerons_0,.g = g);}
  /* at this point, all resurrected objects are marked. */
  /* remove dead objects from weak tables */
  {IPCALL(clearbykeys,ipclearbykeys_0,.g = g,.l = g->ephemeron);}  /* clear keys from all ephemeron */
  {IPCALL(clearbykeys,ipclearbykeys_1,.g = g,.l = g->allweak);}  /* clear keys from all 'allweak' */
  /* clear values from resurrected weak tables */
  {IPCALL(clearbyvalues,ipclearbyvalues_3,.g = g,.l = g->weak,.f = origweak);}
  {IPCALL(clearbyvalues,ipclearbyvalues_2,.g = g,.l = g->allweak,.f = origall);}
  {IPCALL(luaS_clearcache,ipluaS_clearcache_0);}
  {g->currentwhite = cast_byte(otherwhite(g));}  /* flip current white */
  {lua_assert(g->gray == NULL);}
}