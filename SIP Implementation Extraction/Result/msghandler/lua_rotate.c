#include "lua_rotate.h"
void lua_rotateFun(void *p) 
{
    lua_rotate *pIp = (lua_rotate*)p;
  StkId p, t, m;
  lua_lock(pIp -> L);
  t = pIp -> L->top.p - 1;  /* end of stack segment being rotated */
  {StkId index2stack_ret_0;IPCALL(index2stack,ipindex2stack_0,.L = pIp->L,.idx = pIp->idx,.ret = &index2stack_ret_0);p = index2stack_ret_0;}  /* start of segment */
  api_check(pIp -> L, pIp -> L->tbclist.p < p, "moving a to-be-closed slot");
  api_check(pIp -> L, (pIp -> n >= 0 ? pIp -> n : -pIp -> n) <= (t - p + 1), "invalid 'n'");
  m = (pIp -> n >= 0 ? t - pIp -> n : p - pIp -> n - 1);  /* end of prefix */
  {IPCALL(reverse,ipreverse_2,.L = pIp->L,.from = p,.to = m);}  /* reverse the prefix with length 'pIp -> n' */
  {IPCALL(reverse,ipreverse_1,.L = pIp->L,.from = m + 1,.to = t);}  /* reverse the suffix */
  {IPCALL(reverse,ipreverse_0,.L = pIp->L,.from = p,.to = t);}  /* reverse the entire segment */
  lua_unlock(pIp -> L);
}