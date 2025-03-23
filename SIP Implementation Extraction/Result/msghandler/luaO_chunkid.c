#include "luaO_chunkid.h"
void luaO_chunkidFun(void *p) 
{
    luaO_chunkid *pIp = (luaO_chunkid*)p;
  size_t bufflen = LUA_IDSIZE;  /* free space in buffer */
  if (*(pIp->source) == '=') {  /* 'literal' source */
    if ((pIp->srclen) <= bufflen)  /* small enough? */
      memcpy((pIp->out), (pIp->source) + 1, (pIp->srclen) * sizeof(char));
    else {  /* truncate it */
      {addstr(pIp->out, pIp->source + 1, bufflen - 1);}
      *(pIp->out) = '\0';
    }
  }
  else if (*(pIp->source) == '@') {  /* file name */
    if ((pIp->srclen) <= bufflen)  /* small enough? */
      memcpy((pIp->out), (pIp->source) + 1, (pIp->srclen) * sizeof(char));
    else {  /* add '...' before rest of name */
      {addstr(pIp->out, RETS, LL(RETS));}
      {bufflen -= LL(RETS);}
      memcpy((pIp->out), (pIp->source) + 1 + (pIp->srclen) - bufflen, bufflen * sizeof(char));
    }
  }
  else {  /* string; format as [string "source"] */
    const char *nl = strchr((pIp->source), '\n');  /* find first new line (if any) */
    {addstr(pIp->out, PRE, LL(PRE));}  /* add prefix */
    {bufflen -= LL(PRE RETS POS) + 1;}  /* save space for prefix+suffix+'\0' */
    if ((pIp->srclen) < bufflen && nl == NULL) {  /* small one-line source? */
      {addstr(pIp->out, pIp->source, pIp->srclen);}  /* keep it */
    }
    else {
      if (nl != NULL)
        {pIp->srclen = ct_diff2sz(nl - pIp->source);}  /* stop at first newline */
      if ((pIp->srclen) > bufflen) (pIp->srclen) = bufflen;
      {addstr(pIp->out, pIp->source, pIp->srclen);}
      {addstr(pIp->out, RETS, LL(RETS));}
    }
    {memcpy(pIp->out, POS, (LL(POS) + 1) * sizeof(char));}
  }
}