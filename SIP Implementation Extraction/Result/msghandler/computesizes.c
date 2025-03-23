#include "computesizes.h"
void computesizesFun(void *p) 
{
    computesizes *pIp = (computesizes*)p;
  int i;
  unsigned int twotoi;  /* 2^i (candidate for optimal size) */
  unsigned int a = 0;  /* number of elements smaller than 2^i */
  unsigned int na = 0;  /* number of elements to go to array part */
  unsigned int optimal = 0;  /* optimal size for array part */
  /* traverse slices while 'twotoi' does not overflow and total of array
     indices still can satisfy 'arrayXhash' against the array size */
  for (i = 0, twotoi = 1;
       twotoi > 0 && arrayXhash(twotoi, (pIp->ct)->na);
       i++, twotoi *= 2) {
    unsigned nums = (pIp->ct)->nums[i];
    a += nums;
    {if (nums > 0 &&  /* grows array only if it gets more elements... */
        arrayXhash(twotoi, a)) {  /* ...while using "less memory" */
      optimal = twotoi;  /* optimal size (till now) */
      na = a;  /* all elements up to 'optimal' will go to array part */
    }}
  }
  (pIp->ct)->na = na;
  *(pIp->ret) =  optimal;
}