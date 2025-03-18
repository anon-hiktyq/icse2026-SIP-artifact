#include "upvalname.h"
void upvalnameFun(void *p) 
{
    upvalname *pIp = (upvalname*)p;
  TString *s = check_exp(pIp -> uv < pIp -> p->sizeupvalues, pIp -> p->upvalues[pIp -> uv].name);
  if (s == NULL) return "?";
  else return getstr(s);
}