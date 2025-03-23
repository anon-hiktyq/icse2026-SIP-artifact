#include "luaT_getvarargs.h"
void luaT_getvarargsFun(void *p) 
{
    luaT_getvarargs *pIp = (luaT_getvarargs*)p;
  int i;
  int nextra = (pIp->ci)->u.l.nextraargs;
  if ((pIp->wanted) < 0) {
    (pIp->wanted) = nextra;  /* get all extra arguments available */
    {checkstackp(pIp->L, nextra, pIp->where);}  /* ensure stack space */
    (pIp->L)->top.p = (pIp->where) + nextra;  /* next instruction will need top */
  }
  for (i = 0; i < (pIp->wanted) && i < nextra; i++)
    {setobjs2s(pIp->L, pIp->where + i, pIp->ci->func.p - nextra + i);}
  for (; i < (pIp->wanted); i++)   /* complete required results with nil */
    {setnilvalue(s2v(pIp->where + i));}
}