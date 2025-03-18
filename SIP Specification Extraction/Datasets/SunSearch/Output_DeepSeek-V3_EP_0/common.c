
#include "common.h"

/*@ axiomatic Sum_array {
      logic integer sum(int* array, integer begin, integer end) reads array[begin .. (end-1)];
      axiom empty:
        \forall int* a, integer b, e; b >= e ==> sum(a,b,e) == 0;
      axiom range:
        \forall int* a, integer b, e; b < e ==> sum(a,b,e) == sum(a,b,e-1) + a[e-1];
    }
*/

/*@ requires \valid(array + (0..length-1));
    ensures \result == sum(array, 0, length);
*/
int array_sum(int* array, int length) {
    int sum = 0;
    /*@ loop invariant 0 <= i <= length;
        loop invariant sum == sum(array, 0, i);
        loop assigns sum, i;
        loop variant length - i;
    */
    for (int i = 0; i < length; i++) {
        sum += array[i];
    }
    return sum;
}
