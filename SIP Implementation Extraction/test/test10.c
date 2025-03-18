#include "malloc.h"


int foo(int **p, int a){
    **p = a;
    return a;
}
int main(){
    int **p = malloc(4);
    *p = malloc(4);
    foo(p, 2);
}