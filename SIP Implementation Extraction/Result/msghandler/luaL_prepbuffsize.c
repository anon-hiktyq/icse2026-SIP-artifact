#include "luaL_prepbuffsize.h"
void luaL_prepbuffsizeFun(void *p) 
{
    luaL_prepbuffsize *pIp = (luaL_prepbuffsize*)p;
  char * prepbuffsize_ret_0;IPCALL(prepbuffsize,ipprepbuffsize_0,.B = pIp->B,.sz = pIp->sz,.boxidx = -1,.ret = prepbuffsize_ret_0);pIp->ret =  prepbuffsize_ret_0;
}