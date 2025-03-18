
#include "common.h"

/*@ 
requires \valid(arr + (0..n-1));
requires n > 0;
ensures \result == \old(arr[0]) + delta;
assigns arr[0];
*/
int update_first_element(int* arr, int n, int delta) {
    arr[0] += delta;
    return arr[0];
}

/*@ 
requires \valid(p) && \valid(p->next);
ensures \result == \old(p->value) + delta;
assigns p->value;
*/
int update_node_value(struct node* p, int delta) {
    p->value += delta;
    return p->value;
}

/*@ 
requires \valid(arr + (0..n-1));
requires n > 0;
ensures \result == \sum(arr, 0, n);
assigns arr[0..n-1];
*/
int sum_array(int* arr, int n) {
    int sum = 0;
    /*@ loop invariant 0 <= i <= n;
        loop invariant sum == \sum(arr, 0, i);
        loop assigns sum;
        loop variant n - i;
    */
    for (int i = 0; i < n; i++) {
        sum += arr[i];
    }
    return sum;
}
