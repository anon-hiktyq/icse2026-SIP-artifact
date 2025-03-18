
#include "common.h"

/*@ axiomatic Sum_array {
      logic integer sum(int* array, integer begin, integer end) reads array[begin .. (end-1)];
      axiom empty:
      \forall int* a, integer b, e; b >= e ==> sum(a,b,e) == 0;
      axiom range:
      \forall int* a, integer b, e; b < e ==> sum(a,b,e) == sum(a,b,e-1) + a[e-1];
   }
*/

/*@ 
  requires \valid(arr + (0..n-1));
  requires n >= 0;
  ensures \result == sum(arr, 0, n);
  assigns \nothing;
*/
int sum_array(int* arr, int n) {
    int sum = 0;
    /*@ 
      loop invariant 0 <= i <= n;
      loop invariant sum == sum(arr, 0, i);
      loop assigns i, sum;
      loop variant n - i;
    */
    for (int i = 0; i < n; i++) {
        sum += arr[i];
    }
    return sum;
}
