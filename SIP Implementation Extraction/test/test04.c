/// bottom up 3 level


#include "malloc.h"

void add(int *p){
    *p = 2;
}

void bar( int *q){
    add(q);
}

void foo(int *q){
    bar(q);
}

int main(){
    int *p = malloc(4);
    foo(p);
}

