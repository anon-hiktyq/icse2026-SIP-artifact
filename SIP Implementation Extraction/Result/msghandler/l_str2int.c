#include "l_str2int.h"
void l_str2intFun(void *p) 
{
    l_str2int *pIp = (l_str2int*)p;
  lua_Unsigned a = 0;
  int empty = 1;
  int neg;
  while (lisspace(cast_uchar(*(pIp->s)))) (pIp->s)++;  /* skip initial spaces */
  {int isneg_ret_0;IPCALL(isneg,ipisneg_0,.s = pIp->&s,.ret = &isneg_ret_0);neg = isneg_ret_0;}
  if ((pIp->s)[0] == '0' &&
      ((pIp->s)[1] == 'x' || (pIp->s)[1] == 'X')) {  /* hex? */
    (pIp->s) += 2;  /* skip '0x' */
    for (; lisxdigit(cast_uchar(*(pIp->s))); (pIp->s)++) {
      {lu_byte luaO_hexavalue_ret_0;IPCALL(luaO_hexavalue,ipluaO_hexavalue_0,.c = pIp->*s,.ret = &luaO_hexavalue_ret_0);a = a * 16 + luaO_hexavalue_ret_0;}
      empty = 0;
    }
  }
  else {  /* decimal */
    for (; lisdigit(cast_uchar(*(pIp->s))); (pIp->s)++) {
      int d = *(pIp->s) - '0';
      if (a >= MAXBY10 && (a > MAXBY10 || d > MAXLASTD + neg))  /* overflow? */
        pIp->ret =  NULL;  /* do not accept it (as integer) */
      {a = a * 10 + cast_uint(d);}
      empty = 0;
    }
  }
  while (lisspace(cast_uchar(*(pIp->s)))) (pIp->s)++;  /* skip trailing spaces */
  if (empty || *(pIp->s) != '\0') pIp->ret =  NULL;  /* something wrong in the numeral */
  else {
    {*pIp->result = l_castU2S((neg) ? 0u - a : a);}
    pIp->ret =  (pIp->s);
  }
}