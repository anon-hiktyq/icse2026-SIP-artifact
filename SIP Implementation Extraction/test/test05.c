/// recursive

#include "malloc.h"
void foo(int *p, int *q);
void bar(int *p, int *q){
    foo(p, q);
    *q = 3;
}

void foo(int *p, int *q){
    bar(p, q);
    *p = 2;
}

int main(){
    int *p = malloc(4);
    int *q = malloc(4);
    foo(p, q);
}