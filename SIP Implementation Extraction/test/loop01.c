#include "malloc.h"
int bar(int a){
    return a * a;
}

int foo(int *p, int a){
    int e = *p;
    if(e > a){
        return foo(p, e - 1);
    }

    else{
        *p = bar(a);
        return a;
    }
}

int main(){
    int *p = malloc(4);
    *p = 5;
    foo(p, 5);
}