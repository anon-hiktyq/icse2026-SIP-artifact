#include "mainpositionfromnode.h"
void mainpositionfromnodeFun(void *p) 
{
    mainpositionfromnode *pIp = (mainpositionfromnode*)p;
  TValue key;
  getnodekey(cast(lua_State *, NULL), &key, pIp -> nd);
  pIp -> ret = mainpositionTV(t, &key);
}