#include "resizearray.h"
void resizearrayFun(void *p) 
{
    resizearray *pIp = (resizearray*)p;


  if (pIp -> oldasize == pIp -> newasize)
    pIp -> ret = t->array; /* nothing to be done */
  else if (pIp -> newasize == 0) {  /* erasing array? */
    Value *op = pIp -> t->array - pIp -> oldasize;  /* original array's real address */
    luaM_freemem(pIp -> L, op, concretesize(pIp -> oldasize));  /* free it */
    pIp -> ret = NULL;
  }
  else {
    size_t newasizeb = concretesize(pIp -> newasize);
    Value *np = cast(Value *,
                  luaM_reallocvector(pIp -> L, NULL, 0, newasizeb, lu_byte));
    if (np == NULL)  /* allocation error? */
      pIp -> ret = NULL;
    np += pIp -> newasize;  /* shift pointer to the end of value segment */
    if (pIp -> oldasize > 0) {
      /* move common elements to new position */
      size_t oldasizeb = concretesize(pIp -> oldasize);
      Value *op = pIp -> t->array;  /* original array */
      unsigned tomove = (pIp -> oldasize < pIp -> newasize) ? pIp -> oldasize : pIp -> newasize;
      size_t tomoveb = (pIp -> oldasize < pIp -> newasize) ? oldasizeb : newasizeb;
      lua_assert(tomoveb > 0);
      memcpy(np - tomove, op - tomove, tomoveb);
      luaM_freemem(pIp -> L, op - pIp -> oldasize, oldasizeb);  /* free old block */
    }
    pIp -> ret = np;
  }
}