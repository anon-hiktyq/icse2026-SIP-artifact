#include "malloc.h"

/// write before read global
int a;
int foo(int *p){
    a = *p;
    int c = a;
    return c;
}

int main(){
    int *p = malloc(4);
    foo(p);
}