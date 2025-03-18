#include "l_str2d.h"
void l_str2dFun(void *p) 
{
    l_str2d *pIp = (l_str2d*)p;
  const char *endptr;
  const char *pmode = strpbrk(pIp -> s, ".xXnN");  /* look for special chars */
  int mode = pmode ? ltolower(cast_uchar(*pmode)) : 0;
  if (mode == 'n')  /* reject 'inf' and 'nan' */
    pIp -> ret = NULL;
  {const char * l_str2dloc_ret_1;IPCALL(l_str2dloc,ipl_str2dloc_1,.s = pIp->s,.result = pIp->result,.mode = mode,.ret = pIp->l_str2dloc_ret_1);endptr = l_str2dloc_ret_1;}  /* try to convert */
  if (endptr == NULL) {  /* failed? may be a different locale */
    char buff[L_MAXLENNUM + 1];
    const char *pdot = strchr(pIp -> s, '.');
    if (pdot == NULL || strlen(pIp -> s) > L_MAXLENNUM)
      pIp -> ret = NULL; /* string too long or no dot; fail */
    strcpy(buff, pIp -> s);  /* copy string to buffer */
    buff[pdot - pIp -> s] = lua_getlocaledecpoint();  /* correct decimal point */
    {const char * l_str2dloc_ret_0;IPCALL(l_str2dloc,ipl_str2dloc_0,.s = pIp->buff,.result = pIp->result,.mode = mode,.ret = pIp->l_str2dloc_ret_0);endptr = l_str2dloc_ret_0;}  /* try again */
    if (endptr != NULL)
      endptr = pIp -> s + (endptr - buff);  /* make relative to 'pIp -> s' */
  }
  pIp -> ret = endptr;
}