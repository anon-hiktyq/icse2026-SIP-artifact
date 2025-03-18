/// write before read para
#include "malloc.h"
int foo(int *p, int a){
    *p = 3;
    int c = *p;
    return c;
}

int main(){
    int *p = malloc(4);
    foo(p, 2);
}