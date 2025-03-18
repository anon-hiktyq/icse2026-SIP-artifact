#include <stdio.h>

#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define DEBUG_PRINT(x) printf("Debug: %d\n", x)
#define NUM 50

#ifdef DEBUG
void main() {
    int a;
    a = NUM;
    int b = 20;
    int max_value = MAX(a, b);
    DEBUG_PRINT(max_value);
}
#else
void main() {
    printf("Debug is not enabled.\n");
}
#endif