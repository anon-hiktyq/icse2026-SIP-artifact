#include "l_str2dloc.h"
void l_str2dlocFun(l_str2dloc *pIp) 
{
  char *endptr;
  *(pIp -> result) = (pIp -> mode == 'x') ? lua_strx2number(pIp -> s, &endptr)  /* try to convert */
                          : lua_str2number(pIp -> s, &endptr);
  if (endptr == pIp -> s) return NULL;  /* nothing recognized? */
  while (lisspace(cast_uchar(*endptr))) endptr++;  /* skip trailing spaces */
  pIp -> ret = (*endptr == '\0') ? endptr : NULL; /* OK iff no trailing chars */
}