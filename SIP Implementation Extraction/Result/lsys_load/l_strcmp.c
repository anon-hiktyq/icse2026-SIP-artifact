#include "l_strcmp.h"
void l_strcmpFun(void *p) 
{
    l_strcmp *pIp = (l_strcmp*)p;
  size_t rl1;  /* real length */
  const char *s1 = getlstr(pIp -> ts1, rl1);
  size_t rl2;
  const char *s2 = getlstr(pIp -> ts2, rl2);
  for (;;) {  /* for each segment */
    int temp = strcoll(s1, s2);
    if (temp != 0)  /* not equal? */
      *(pIp -> ret) = temp; /* done */
    else {  /* strings are equal up to a '\0' */
      size_t zl1 = strlen(s1);  /* index of first '\0' in 's1' */
      size_t zl2 = strlen(s2);  /* index of first '\0' in 's2' */
      if (zl2 == rl2)  /* 's2' is finished? */
        *(pIp -> ret) = (zl1 == rl1) ? 0 : 1; /* check 's1' */
      else if (zl1 == rl1)  /* 's1' is finished? */
        *(pIp -> ret) = -1; /* 's1' is less than 's2' ('s2' is not finished) */
      /* both strings longer than 'zl'; go on comparing after the '\0' */
      zl1++; zl2++;
      s1 += zl1; rl1 -= zl1; s2 += zl2; rl2 -= zl2;
    }
  }
}