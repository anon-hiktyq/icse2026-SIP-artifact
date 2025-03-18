#include "rname.h"
void rnameFun(void *p) 
{
    rname *pIp = (rname*)p;
  const char *what;{const char * basicgetobjname_ret_0;IPCALL(basicgetobjname,ipbasicgetobjname_0,.p = pIp->p,.ppc = &pc,.reg = c,.name = pIp->name,.ret = basicgetobjname_ret_0);*what = basicgetobjname_ret_0} /* search for 'pIp -> c' */
  if (!(what && *what == 'pIp -> c'))  /* did not find a constant pIp -> name? */
    pIp -> *name = "?";
}