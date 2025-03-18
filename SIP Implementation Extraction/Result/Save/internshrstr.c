#include "internshrstr.h"
void internshrstrFun(void *p) 
{
    internshrstr *pIp = (internshrstr*)p;
  TString *ts;
  global_State *g = G(pIp -> L);
  stringtable *tb = &g->strt;
  unsigned int h;{unsigned int luaS_hash_ret_1;IPCALL(luaS_hash,ipluaS_hash_0,.str = pIp->str,.l = pIp->l,.seed = g->seed,.ret = pIp->&luaS_hash_ret_1);h = luaS_hash_ret_1}
  TString **list = &tb->hash[lmod(h, tb->size)];
  lua_assert(pIp -> str != NULL);  /* otherwise 'memcmp'/'memcpy' are undefined */
  for (ts = *list; ts != NULL; ts = ts->u.hnext) {
    if (pIp -> l == cast_uint(ts->shrlen) &&
        (memcmp(pIp -> str, getshrstr(ts), pIp -> l * sizeof(char)) == 0)) {
      /* found! */
      if (isdead(g, ts))  /* dead (but not collected yet)? */
        changewhite(ts);  /* resurrect it */
      pIp -> ret = ts;
    }
  }
  /* else must create a new string */
  if (tb->nuse >= tb->size) {  /* need to grow string table? */
    {IPCALL(growstrtab,ipgrowstrtab_0,.L = pIp->L,.tb = tb);}
    list = &tb->hash[lmod(h, tb->size)];  /* rehash with new size */
  }
  {TString * createstrobj_ret_0;IPCALL(createstrobj,ipcreatestrobj_0,.pIp->L = pIp->pIp->L,.totalsize = sizestrshr(pIp->l),.tag = LUA_VSHRSTR,.h = h,.pIp->ret = pIp->createstrobj_ret_0);ts = createstrobj_ret_0;}
  ts->shrlen = cast(ls_byte, pIp -> l);
  getshrstr(ts)[pIp -> l] = '\0';  /* ending 0 */
  memcpy(getshrstr(ts), pIp -> str, pIp -> l * sizeof(char));
  ts->u.hnext = *list;
  *list = ts;
  tb->nuse++;
  pIp -> ret = ts;
}