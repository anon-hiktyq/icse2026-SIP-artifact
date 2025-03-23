#include "luaG_getfuncline.h"
void luaG_getfunclineFun(void *p) 
{
    luaG_getfuncline *pIp = (luaG_getfuncline*)p;
  if ((pIp->f)->lineinfo == NULL)  /* no debug information? */
    *(pIp->ret) =  -1;
  else {
    int basepc;
    int baseline;{int getbaseline_ret_0; IPCALL(getbaseline,ipgetbaseline_0,.f = pIp->f,.pc = pIp->pc,.basepc = &basepc,.ret = &getbaseline_ret_0);baseline = getbaseline_ret_0;}
    while (basepc++ < (pIp->pc)) {  /* walk until given instruction */
      {lua_assert(pIp->f->lineinfo[basepc] != ABSLINEINFO);}
      baseline += (pIp->f)->lineinfo[basepc];  /* correct line */
    }
    *(pIp->ret) =  baseline;
  }
}