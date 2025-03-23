#include "auxgetinfo.h"
void auxgetinfoFun(void *p) 
{
    auxgetinfo *pIp = (auxgetinfo*)p;
  int status = 1;
  for (; *(pIp->what); (pIp->what)++) {
    switch (*(pIp->what)) {
      case 'S': {
        {IPCALL(funcinfo,ipfuncinfo_0,.ar = pIp->ar,.cl = pIp->f);}
        break;
      }
      case 'l': {
        {int getcurrentline_ret_0;IPCALL(getcurrentline,ipgetcurrentline_0,.ci = pIp->ci,.ret = &getcurrentline_ret_0);pIp->ar->currentline = (pIp->ci && isLua(pIp->ci)) ? getcurrentline_ret_0 : -1;}
        break;
      }
      case 'u': {
        (pIp->ar)->nups = ((pIp->f) == NULL) ? 0 : (pIp->f)->c.nupvalues;
        {if (!LuaClosure(pIp->f)) {
          (pIp->ar)->isvararg = 1;
          (pIp->ar)->nparams = 0;
        }
        else {
          (pIp->ar)->isvararg = ((pIp->f)->l.p->flag & PF_ISVARARG) ? 1 : 0;
          (pIp->ar)->nparams = (pIp->f)->l.p->numparams;
        }}
        break;
      }
      case 't': {
        if ((pIp->ci) != NULL) {
          (pIp->ar)->istailcall = !!((pIp->ci)->callstatus & CIST_TAIL);
          {pIp->ar->extraargs =
                   cast_uchar((pIp->ci->callstatus & MAX_CCMT) >> CIST_CCMT);}
        }
        else {
          (pIp->ar)->istailcall = 0;
          (pIp->ar)->extraargs = 0;
        }
        break;
      }
      case 'n': {
        {const char * getfuncname_ret_0;IPCALL(getfuncname,ipgetfuncname_0,.L = pIp->L,.ci = pIp->ci,.name = &ar->name,.ret = getfuncname_ret_0);pIp->ar->namewhat = getfuncname_ret_0;}
        if ((pIp->ar)->namewhat == NULL) {
          (pIp->ar)->namewhat = "";  /* not found */
          (pIp->ar)->name = NULL;
        }
        break;
      }
      case 'r': {
        if ((pIp->ci) == NULL || !((pIp->ci)->callstatus & CIST_HOOKED))
          (pIp->ar)->ftransfer = (pIp->ar)->ntransfer = 0;
        else {
          (pIp->ar)->ftransfer = (pIp->L)->transferinfo.ftransfer;
          (pIp->ar)->ntransfer = (pIp->L)->transferinfo.ntransfer;
        }
        break;
      }
      case 'L':
      case 'f':  /* handled by lua_getinfo */
        break;
      default: status = 0;  /* invalid option */
    }
  }
  *(pIp->ret) =  status;
}