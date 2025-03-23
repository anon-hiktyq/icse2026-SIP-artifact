#include "changedline.h"
void changedlineFun(void *p) 
{
    changedline *pIp = (changedline*)p;
  if ((pIp->p)->lineinfo == NULL)  /* no debug information? */
    *(pIp->ret) =  0;
  if ((pIp->newpc) - (pIp->oldpc) < MAXIWTHABS / 2) {  /* not too far apart? */
    int delta = 0;  /* line difference */
    int pc = (pIp->oldpc);
    for (;;) {
      int lineinfo = (pIp->p)->lineinfo[++pc];
      if (lineinfo == ABSLINEINFO)
        break;  /* cannot compute delta; fall through */
      delta += lineinfo;
      if (pc == (pIp->newpc))
        *(pIp->ret) =  (delta != 0);  /* delta computed successfully */
    }
  }
  /* either instructions are too far apart or there is an absolute line
     info in the way; compute line difference explicitly */
  int luaG_getfuncline_ret_0;IPCALL(luaG_getfuncline,ipluaG_getfuncline_0,.f = pIp->p,.pc = pIp->newpc,.ret = &luaG_getfuncline_ret_0);*(pIp->ret) =  (luaG_getfuncline(p, oldpc) != luaG_getfuncline_ret_0);
}