#include "keyinarray.h"
void keyinarrayFun(void *p) 
{
    keyinarray *pIp = (keyinarray*)p;
  *(pIp -> ret) = (ttisinteger(key)) ? ikeyinarray(t, ivalue(key)) : 0;
}