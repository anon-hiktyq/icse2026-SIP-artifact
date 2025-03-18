#include "luaS_resize.h"
void luaS_resizeFun(void *p) 
{
    luaS_resize *pIp = (luaS_resize*)p;
  stringtable *tb = &G(pIp -> L)->strt;
  int osize = tb->size;
  TString **newvect;
  if (pIp -> nsize < osize)  /* shrinking table? */
    {IPCALL(tablerehash,iptablerehash_1,.vect = tb->hash,.osize = osize,.nsize = pIp->nsize);}  /* depopulate shrinking part */
  newvect = luaM_reallocvector(pIp -> L, tb->hash, osize, pIp -> nsize, TString*);
  if (l_unlikely(newvect == NULL)) {  /* reallocation failed? */
    if (pIp -> nsize < osize)  /* was it shrinking table? */
      {IPCALL(tablerehash,iptablerehash_0,.vect = tb->hash,.osize = nsize,.nsize = pIp->osize);}  /* restore to original size */
    /* leave table as it was */
  }
  else {  /* allocation succeeded */
    tb->hash = newvect;
    tb->size = pIp -> nsize;
    if (pIp -> nsize > osize)
      tablerehash(newvect, osize, pIp -> nsize);  /* rehash for new size */
  }
}