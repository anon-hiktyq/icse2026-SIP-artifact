#include "malloc.h"

int foo(int *p, int b){
    int *q = &b;
    int **a = malloc(4);
    if(b > 0)
        *a = p;
    else
        *a = q;
    int *t = *a;
    *t = b;
    int c = *p;
    return c;
}

int main(){
    int *p = malloc(4);
    foo(p, 4);
}