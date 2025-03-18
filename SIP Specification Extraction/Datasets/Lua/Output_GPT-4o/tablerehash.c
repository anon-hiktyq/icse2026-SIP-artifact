
#include <stddef.h>

// Definition of a linked list node
struct node {
    int value;
    struct node* next;
};

/*@
    // Predicate to define a valid linked list
    predicate valid_list(struct node* n) = 
        n == NULL || (\valid(n) && valid_list(n->next));

    // Predicate to define the length of a linked list
    logic integer list_length(struct node* n) =
        n == NULL ? 0 : 1 + list_length(n->next);
*/

/*@
    requires valid_list(head);
    assigns \nothing;
    ensures \result == list_length(head);
*/
int length_of_list(struct node* head) {
    int length = 0;
    struct node* current = head;
    
    /*@ 
        loop invariant valid_list(current);
        loop invariant length == list_length(head) - list_length(current);
        loop assigns current, length;
        loop variant list_length(current);
    */
    while (current != NULL) {
        length++;
        current = current->next;
    }
    
    return length;
}
