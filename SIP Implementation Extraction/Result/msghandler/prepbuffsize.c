#include "prepbuffsize.h"
void prepbuffsizeFun(void *p) 
{
    prepbuffsize *pIp = (prepbuffsize*)p;
  {checkbufferlevel(pIp->B, pIp->boxidx);}
  if ((pIp->B)->size - (pIp->B)->n >= (pIp->sz))  /* enough space? */
    pIp->ret =  (pIp->B)->b + (pIp->B)->n;
  else {
    lua_State *L = (pIp->B)->L;
    char *newbuff;
    size_t newsize;{size_t newbuffsize_ret_0; IPCALL(newbuffsize,ipnewbuffsize_0,.B = pIp->B,.sz = pIp->sz,.ret = &newbuffsize_ret_0);newsize = newbuffsize_ret_0;}
    /* create larger buffer */
    {if (buffonstack(pIp->B))  /* buffer already has a box? */
      {void * resizebox_ret_0;IPCALL(resizebox,ipresizebox_0,.L = L,.idx = pIp->boxidx,.newsize = newsize,.ret = resizebox_ret_0);newbuff = (char *)resizebox_ret_0;}  /* resize it */
    else {  /* no box yet */
      {lua_remove(L, pIp->boxidx);}  /* remove placeholder */
      {IPCALL(newbox,ipnewbox_0,.L = L);}  /* create a new box */
      {lua_insert(L, pIp->boxidx);}  /* move box to its intended position */
      {IPCALL(lua_toclose,iplua_toclose_0);}
      {void * resizebox_ret_1;IPCALL(resizebox,ipresizebox_1,.L = L,.idx = pIp->boxidx,.newsize = newsize,.ret = resizebox_ret_1);newbuff = (char *)resizebox_ret_1;}
      memcpy(newbuff, (pIp->B)->b, (pIp->B)->n * sizeof(char));  /* copy original content */
    }}
    (pIp->B)->b = newbuff;
    (pIp->B)->size = newsize;
    pIp->ret =  newbuff + (pIp->B)->n;
  }
}