
#include "l_str2dloc.h"

/*@ axiomatic StringToNumber {
      logic integer string_to_number(char* s, char** endptr, char mode);
      axiom hex_conversion:
        \forall char* s, char** endptr; 
          string_to_number(s, endptr, 'x') == lua_strx2number(s, endptr);
      axiom dec_conversion:
        \forall char* s, char** endptr; 
          string_to_number(s, endptr, 'd') == lua_str2number(s, endptr);
    }
*/

/*@
  requires \valid(pIp) && \valid(pIp->s) && \valid(pIp->result);
  requires pIp->mode == 'x' || pIp->mode == 'd';
  assigns pIp->result, pIp->ret;
  ensures (pIp->ret == \null) ==> (*pIp->result == 0);
  ensures (pIp->ret != \null) ==> (*pIp->result == string_to_number(pIp->s, &endptr, pIp->mode));
*/
void l_str2dlocFun(l_str2dloc *pIp) 
{
  char *endptr;
  /*@ assert \valid(pIp->s) && \valid(pIp->result); */
  *(pIp -> result) = (pIp -> mode == 'x') ? lua_strx2number(pIp -> s, &endptr)  /* try to convert */
                          : lua_str2number(pIp -> s, &endptr);
  /*@ assert \valid(&endptr); */
  if (endptr == pIp -> s) return NULL;  /* nothing recognized? */
  /*@ loop invariant \valid(endptr);
      loop assigns endptr;
      loop variant \max(0, \at(pIp->s + \strlen(pIp->s) - endptr, Pre));
  */
  while (lisspace(cast_uchar(*endptr))) endptr++;  /* skip trailing spaces */
  pIp -> ret = (*endptr == '\0') ? endptr : NULL; /* OK iff no trailing chars */
}
