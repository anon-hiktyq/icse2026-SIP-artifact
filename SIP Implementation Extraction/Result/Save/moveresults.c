#include "moveresults.h"
void moveresultsFun(void *p) 
{
    moveresults *pIp = (moveresults*)p;
  switch ((pIp->fwanted)) {  /* handle typical cases separately */
    case 0 + 1:  /* no values needed */
      (pIp->L)->top.p = (pIp->res);
      return;
    case 1 + 1:  /* one value needed */
      if ((pIp->nres) == 0)   /* no results? */
        {setnilvalue(s2v(pIp->res));}  /* adjust with nil */
      else  /* at least one result */
        {setobjs2s(pIp->L, pIp->res, pIp->L->top.p - pIp->nres);}  /* move it to proper place */
      (pIp->L)->top.p = (pIp->res) + 1;
      return;
    case LUA_MULTRET + 1:
      {IPCALL(genmoveresults,ipgenmoveresults_1,.L = pIp->L,.res = pIp->res,.nres = pIp->nres,.wanted = pIp->nres);}  /* we want all results */
      break;
    default: {  /* two/more results and/or to-be-closed variables */
      int wanted;{wanted = get_nresults(pIp->fwanted);}
      if ((pIp->fwanted) & CIST_TBC) {  /* to-be-closed variables? */
        (pIp->L)->ci->u2.nres = (pIp->nres);
        (pIp->L)->ci->callstatus |= CIST_CLSRET;  /* in case of yields */
        {StkId luaF_close_ret_0;IPCALL(luaF_close,ipluaF_close_0,.ret = &luaF_close_ret_0);pIp->res = luaF_close_ret_0;}
        (pIp->L)->ci->callstatus &= ~CIST_CLSRET;
        if ((pIp->L)->hookmask) {  /* if needed, call hook after '__close's */
          ptrdiff_t savedres;{savedres = savestack(pIp->L, pIp->res);}
          {IPCALL(rethook,iprethook_0,.L = pIp->L,.ci = L->ci,.nres = pIp->nres);}
          {pIp->res = restorestack(pIp->L, savedres);}  /* hook can move stack */
        }
        if (wanted == LUA_MULTRET)
          wanted = (pIp->nres);  /* we want all results */
      }
      {IPCALL(genmoveresults,ipgenmoveresults_0,.L = pIp->L,.res = pIp->res,.nres = pIp->nres,.wanted = wanted);}
      break;
    }
  }
}