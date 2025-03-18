#include "resizebox.h"
void resizeboxFun(void *p) 
{
    resizebox *pIp = (resizebox*)p;
  UBox *box;{void * lua_touserdata_ret_2;IPCALL(lua_touserdata,iplua_touserdata_0,.ret = pIp->lua_touserdata_ret_2);*box = (UBox *)lua_touserdata_ret_2}
  if (box->bsize == pIp -> newsize)  /* not changing size? */
    pIp -> ret = box->box; /* keep the buffer */
  else {
    void *ud;
    lua_Alloc allocf;{lua_Alloc lua_getallocf_ret_1;IPCALL(lua_getallocf,iplua_getallocf_0,.ret = pIp->&lua_getallocf_ret_1);allocf = lua_getallocf_ret_1}
    void *temp = allocf(ud, box->box, box->bsize, pIp -> newsize);
    if (l_unlikely(temp == NULL && pIp -> newsize > 0)) {  /* allocation error? */
      lua_pushliteral(pIp -> L, "not enough memory");
      {int lua_error_ret_0;IPCALL(lua_error,iplua_error_0,.ret = pIp->&lua_error_ret_0);}  /* raise a memory error */
    }
    box->box = temp;
    box->bsize = pIp -> newsize;
    pIp -> ret = temp;
  }
}