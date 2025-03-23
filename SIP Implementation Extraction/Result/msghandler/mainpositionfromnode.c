#include "mainpositionfromnode.h"
void mainpositionfromnodeFun(void *p) 
{
    mainpositionfromnode *pIp = (mainpositionfromnode*)p;
  TValue key;
  getnodekey(cast(lua_State *, NULL), &key, (pIp->nd));
  Node * mainpositionTV_ret_0;IPCALL(mainpositionTV,ipmainpositionTV_0,.t = pIp->t,.key = &key,.ret = mainpositionTV_ret_0);pIp->ret =  mainpositionTV_ret_0;
}