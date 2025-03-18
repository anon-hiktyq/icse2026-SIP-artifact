
#include "luaO_chunkid.h"

/*@ axiomatic StringOperations {
      logic integer string_length(char* str) reads str[..];
      axiom string_length_def:
        \forall char* str; string_length(str) == (\exists integer n; str[n] == '\0' && \forall integer i; 0 <= i < n ==> str[i] != '\0');
    }
*/

/*@
  requires \valid(pIp);
  requires \valid(pIp->source + (0 .. pIp->srclen - 1));
  requires \valid(pIp->out + (0 .. LUA_IDSIZE - 1));
  requires pIp->srclen >= 0;
  assigns pIp->out[0 .. LUA_IDSIZE - 1];
  ensures \forall size_t i; 0 <= i < LUA_IDSIZE ==> pIp->out[i] == \old(pIp->out[i]) || 
          (i < pIp->srclen && pIp->out[i] == \old(pIp->source[i + 1])) ||
          (i >= pIp->srclen && pIp->out[i] == '\0');
*/
void luaO_chunkidFun(luaO_chunkid *pIp) 
{
  size_t bufflen = LUA_IDSIZE;  /* free space in buffer */
  
  if (*(pIp -> source) == '=') {  /* 'literal' pIp -> source */
    if (pIp -> srclen <= bufflen)  /* small enough? */
      memcpy(pIp -> out, pIp -> source + 1, pIp -> srclen * sizeof(char));
    else {  /* truncate it */
      addstr(pIp -> out, pIp -> source + 1, bufflen - 1);
      *(pIp -> out)= '\0';
    }
  }
  else if (*(pIp -> source) == '@') {  /* file name */
    if (pIp -> srclen <= bufflen)  /* small enough? */
      memcpy(pIp -> out, pIp -> source + 1, pIp -> srclen * sizeof(char));
    else {  /* add '...' before rest of name */
      addstr(pIp -> out, RETS, LL(RETS));
      bufflen -= LL(RETS);
      memcpy(pIp -> out, pIp -> source + 1 + pIp -> srclen - bufflen, bufflen * sizeof(char));
    }
  }
  else {  /* string; format as [string "source"] */
    const char *nl = strchr(pIp -> source, '\n');  /* find first new line (if any) */
    addstr(pIp -> out, PRE, LL(PRE));  /* add prefix */
    bufflen -= LL(PRE RETS POS) + 1;  /* save space for prefix+suffix+'\0' */
    if (pIp -> srclen < bufflen && nl == NULL) {  /* small one-line pIp -> source? */
      addstr(pIp -> out, pIp -> source, pIp -> srclen);  /* keep it */
    }
    else {
      if (nl != NULL)
        pIp -> srclen = ct_diff2sz(nl - pIp -> source);  /* stop at first newline */
      if (pIp -> srclen== bufflen){
      addstr(pIp -> out, pIp -> source, pIp -> srclen);
      addstr(pIp -> out, RETS, LL(RETS));
    }
    memcpy(pIp -> out, POS, (LL(POS) + 1) * sizeof(char));
  }
}
}
