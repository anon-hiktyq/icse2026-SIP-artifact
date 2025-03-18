/// state variable
#include "malloc.h"
int a;
const int b=1;

int foo(int *p){
  *p = a;
  a=b;
  int c=*p;
  return c;
}
