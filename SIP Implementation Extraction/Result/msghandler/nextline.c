#include "nextline.h"
void nextlineFun(void *p) 
{
    nextline *pIp = (nextline*)p;
  if ((pIp->p)->lineinfo[(pIp->pc)] != ABSLINEINFO)
    *(pIp->ret) =  (pIp->currentline) + (pIp->p)->lineinfo[(pIp->pc)];
  else
    int luaG_getfuncline_ret_0;IPCALL(luaG_getfuncline,ipluaG_getfuncline_0,.f = pIp->p,.pc = pIp->pc,.ret = &luaG_getfuncline_ret_0);*(pIp->ret) =  luaG_getfuncline_ret_0;
}