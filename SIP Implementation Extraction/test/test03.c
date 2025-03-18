#include "malloc.h"

/// multi return
int* foo(int c){
    int *a = malloc(4);
    int *b = malloc(4);
    if(c)
        return a;
    else
        return b;
}