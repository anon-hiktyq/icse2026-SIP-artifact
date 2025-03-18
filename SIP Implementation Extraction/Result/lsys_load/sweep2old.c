#include "sweep2old.h"
void sweep2oldFun(void *p) 
{
    sweep2old *pIp = (sweep2old*)p;
  GCObject *curr;
  global_State *g = G(pIp -> L);
  while ((curr = pIp -> *p) != NULL) {
    if (iswhite(curr)) {  /* is 'curr' dead? */
      lua_assert(isdead(g, curr));
      pIp -> *p = curr->next;  /* remove 'curr' from list */
      {IPCALL(freeobj,ipfreeobj_0,.L = pIp->L,.o = curr);}  /* erase 'curr' */
    }
    else {  /* all surviving objects become old */
      setage(curr, G_OLD);
      if (curr->tt == LUA_VTHREAD) {  /* threads must be watched */
        lua_State *th = gco2th(curr);
        linkgclist(th, g->grayagain);  /* insert into 'grayagain' list */
      }
      else if (curr->tt == LUA_VUPVAL && upisopen(gco2upv(curr)))
        set2gray(curr);  /* open upvalues are always gray */
      else  /* everything else is black */
        nw2black(curr);
      pIp -> p = &curr->next;  /* go to next element */
    }
  }
}