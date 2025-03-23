#include "setnodevector.h"
void setnodevectorFun(void *p) 
{
    setnodevector *pIp = (setnodevector*)p;
  if ((pIp->size) == 0) {  /* no elements to hash part? */
    {pIp->t->node = cast(Node *, dummynode);}  /* use common 'dummynode' */
    (pIp->t)->lsizenode = 0;
    {setdummy(pIp->t);}  /* signal that it is using dummy node */
  }
  else {
    int i;
    int lsize;{lu_byte luaO_ceillog2_ret_0; IPCALL(luaO_ceillog2,ipluaO_ceillog2_0,.ret = &luaO_ceillog2_ret_0);lsize = luaO_ceillog2_ret_0;}
    if (lsize > MAXHBITS || (1 << lsize) > MAXHSIZE)
      {IPCALL(luaG_runerror,ipluaG_runerror_0);}
    {pIp->size = twoto(lsize);}
    if (lsize < LIMFORLAST)  /* no 'lastfree' field? */
      {pIp->t->node = luaM_newvector(pIp->L, pIp->size, Node);}
    else {
      size_t bsize = (pIp->size) * sizeof(Node) + sizeof(Limbox);
      char node;{node = luaM_newblock(pIp->L, bsize);}
      {pIp->t->node = cast(Node *, node + sizeof(Limbox));}
      {getlastfree(pIp->t) = gnode(pIp->t, pIp->size);}  /* all positions are free */
    }
    {pIp->t->lsizenode = cast_byte(lsize);}
    {setnodummy(pIp->t);}
    for (i = 0; i < cast_int((pIp->size)); i++) {
      Node n;{n = gnode(pIp->t, i);}
      {gnext(n) = 0;}
      {setnilkey(n);}
      {setempty(gval(n));}
    }
  }
}