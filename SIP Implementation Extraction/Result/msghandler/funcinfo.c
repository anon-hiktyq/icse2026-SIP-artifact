#include "funcinfo.h"
void funcinfoFun(void *p) 
{
    funcinfo *pIp = (funcinfo*)p;
  if (!LuaClosure(pIp -> cl)) {
    pIp -> ar->source = "=[C]";
    pIp -> ar->srclen = LL("=[C]");
    pIp -> ar->linedefined = -1;
    pIp -> ar->lastlinedefined = -1;
    pIp -> ar->what = "C";
  }
  else {
    const Proto *p = pIp -> cl->l.p;
    if (p->source) {
      pIp -> ar->source = getlstr(p->source, pIp -> ar->srclen);
    }
    else {
      pIp -> ar->source = "=?";
      pIp -> ar->srclen = LL("=?");
    }
    pIp -> ar->linedefined = p->linedefined;
    pIp -> ar->lastlinedefined = p->lastlinedefined;
    pIp -> ar->what = (pIp -> ar->linedefined == 0) ? "main" : "Lua";
  }
  {IPCALL(luaO_chunkid,ipluaO_chunkid_0);}
}