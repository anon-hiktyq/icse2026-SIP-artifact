/// write before read para, but para point to multi object
#include "malloc.h"
int foo(int *p, int a){
    *p = a;
    int c = *p;
    return c;
}

int main(){
    int *p = malloc(4);
    foo(p, 2);
    int *q = malloc(4);
    foo(q, 3);
}