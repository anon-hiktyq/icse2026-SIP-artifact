#include "f_pintern.h"
void f_pinternFun(void *p) 
{
    f_pintern *pIp = (f_pintern*)p;
  struct NewExt *ne = cast(struct NewExt *, pIp -> ud);
  {TString * internshrstr_ret_0;IPCALL(internshrstr,ipinternshrstr_0,.L = pIp->L,.str = ne->s,.l = ne->len,.ret = internshrstr_ret_0);ne->ts = internshrstr_ret_0;}
}