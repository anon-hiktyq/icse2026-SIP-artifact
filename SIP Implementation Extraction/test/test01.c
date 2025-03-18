#include "malloc.h"
int a = 2;

int foo(int *p, int b){
    int *q = p;
    *q = b;
    a = *q;
    int c = b;
    return c;
}

int main(){
    int *t = malloc(4);
    foo(t, 4);
}


