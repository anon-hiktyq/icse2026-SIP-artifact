
#include "l_str2dloc.h"
#include <stdlib.h>  // For strtod
#include <ctype.h>   // For isspace

/*@ axiomatic StringLength {
      logic integer string_length(char *s) reads s[0..];
      axiom string_length_null: 
        \forall char *s; *s == '\0' ==> string_length(s) == 0;
      axiom string_length_step: 
        \forall char *s; *s != '\0' ==> string_length(s) == 1 + string_length(s + 1);
    }
*/

/*@
  requires \valid(pIp);
  requires \valid(pIp->result);
  requires \valid(pIp->s);
  assigns pIp->result, pIp->ret;
  ensures (pIp->ret == \null) || (pIp->ret == pIp->s + string_length(pIp->s));
*/
void l_str2dlocFun(l_str2dloc *pIp) 
{
  char *endptr;
  /*@ assert \valid(pIp->s); */
  *(pIp -> result) = (pIp -> mode == 'x') ? lua_strx2number(pIp -> s, &endptr)  /* try to convert */
                          : lua_str2number(pIp -> s, &endptr);
  /*@ assert \valid(endptr); */
  if (endptr == pIp -> s) return;  /* nothing recognized? */
  /*@ loop invariant \valid(endptr);
      loop assigns endptr;
      loop variant string_length(pIp->s) - (endptr - pIp->s);
  */
  while (isspace((unsigned char)(*endptr))) endptr++;  /* skip trailing spaces */
  pIp -> ret = (*endptr == '\0') ? endptr : NULL; /* OK iff no trailing chars */
}
