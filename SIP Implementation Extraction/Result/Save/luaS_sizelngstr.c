#include "luaS_sizelngstr.h"
void luaS_sizelngstrFun(void *p) 
{
    luaS_sizelngstr *pIp = (luaS_sizelngstr*)p;
  switch ((pIp->kind)) {
    case LSTRREG:  /* regular long string */
      /* don't need 'falloc'/'ud', but need space for content */
      *(pIp->ret) =  offsetof(TString, falloc) + ((pIp->len) + 1) * sizeof(char);
    case LSTRFIX:  /* fixed external long string */
      /* don't need 'falloc'/'ud' */
      *(pIp->ret) =  offsetof(TString, falloc);
    default:  /* external long string with deallocation */
      {lua_assert(pIp->kind == LSTRMEM);}
      *(pIp->ret) =  sizeof(TString);
  }
}