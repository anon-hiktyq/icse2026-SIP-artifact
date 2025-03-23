#include "resizebox.h"
void resizeboxFun(void *p) 
{
    resizebox *pIp = (resizebox*)p;
  UBox box;{void * lua_touserdata_ret_0; IPCALL(lua_touserdata,iplua_touserdata_0,.ret = lua_touserdata_ret_0);box = (UBox *)lua_touserdata_ret_0;}
  if (box->bsize == (pIp->newsize))  /* not changing size? */
    pIp->ret =  box->box;  /* keep the buffer */
  else {
    void *ud;
    lua_Alloc allocf;{lua_Alloc lua_getallocf_ret_0; IPCALL(lua_getallocf,iplua_getallocf_0,.ret = &lua_getallocf_ret_0);allocf = lua_getallocf_ret_0;}
    void *temp = allocf(ud, box->box, box->bsize, (pIp->newsize));
    {if (l_unlikely(temp == NULL && pIp->newsize > 0)) {  /* allocation error? */
      {lua_pushliteral(pIp->L, "not enough memory");}
      {int lua_error_ret_0;IPCALL(lua_error,iplua_error_0,.ret = &lua_error_ret_0);lua_error_ret_0;}  /* raise a memory error */
    }}
    box->box = temp;
    box->bsize = (pIp->newsize);
    pIp->ret =  temp;
  }
}