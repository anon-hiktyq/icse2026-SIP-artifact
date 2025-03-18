#include "luaF_protosize.h"
void luaF_protosizeFun(void *p) 
{
    luaF_protosize *pIp = (luaF_protosize*)p;
  lu_mem sz = cast(lu_mem, sizeof(Proto))
            + cast_uint(pIp -> p->sizep) * sizeof(Proto*)
            + cast_uint(pIp -> p->sizek) * sizeof(TValue)
            + cast_uint(pIp -> p->sizelocvars) * sizeof(LocVar)
            + cast_uint(pIp -> p->sizeupvalues) * sizeof(Upvaldesc);
  if (!(pIp -> p->flag & PF_FIXED)) {
    sz += cast_uint(pIp -> p->sizecode) * sizeof(Instruction);
    sz += cast_uint(pIp -> p->sizelineinfo) * sizeof(lu_byte);
    sz += cast_uint(pIp -> p->sizeabslineinfo) * sizeof(AbsLineInfo);
  }
  *(pIp -> ret) = sz;
}