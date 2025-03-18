#include "save.h"
void saveFun(void *p) 
{
    save *pIp = (save*)p;
  Mbuffer *b = pIp -> ls->buff;
  if (luaZ_bufflen(b) + 1 > luaZ_sizebuffer(b)) {
    size_t newsize;
    if (luaZ_sizebuffer(b) >= MAX_SIZE/2)
      {IPCALL(lexerror,iplexerror_0,.ls = pIp->ls,.msg = "lexical element too long",.token = 0);}
    newsize = luaZ_sizebuffer(b) * 2;
    luaZ_resizebuffer(pIp -> ls->L, b, newsize);
  }
  b->buffer[luaZ_bufflen(b)++] = cast_char(pIp -> c);
}