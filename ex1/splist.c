#include <stdlib.h>
#include "splist.h"

typedef struct splist_node splist_node_t;
struct splist_node {
    splist_node_t* next;
    element_t* data;
};

struct splist {
    splist_node_t* head;
    // more fields can be added
};

// Create and allocate memory for a new list.
splist_t* spl_create(){
    //TODO: implement 'create' method
    return NULL;
}

// Returns the number of elements in the list.
int spl_size(splist_t* list){
    //TODO: implement 'size' method
    return 0;
}

/* Important note: to implement any list manipulation operator (insert, append, delete, sort, ...), always be aware of the following cases:
 * 1. empty list ==> avoid errors
 * 2. do operation at the start of the list ==> typically requires some special pointer manipulation
 * 3. do operation at the end of the list ==> typically requires some special pointer manipulation
 * 4. do operation in the middle of the list ==> default case with default pointer manipulation
 * ALWAYS check that you implementation works correctly in all these cases (check this on paper with list representation drawings!)
 **/
splist_t* spl_insert_at_reference(splist_t* list, element_t* element, splist_node_t* reference){
    splist_node_t* new_node = malloc(sizeof(splist_node_t));
    new_node->data = element;

    if (list->head == NULL) { // covers case 1
        //TODO: add your code here
        list->head = new_node;
        new_node->next = NULL;

    } else if (list->head == reference) {  // covers case 2
        //TODO: add your code here
        list->head = new_node;
        new_node->next = reference;

    } else if (reference == NULL) { // covers case 3
        //TODO: add your code here
        
    } else {  // covers case 4
        //TODO: add your code here
    }
    return list;
}

// Returns the element contained in the list node with reference 'reference' in the list.
element_t* spl_get_element_at_reference(splist_t* list, splist_node_t* reference) {
    //TODO: implement get_element method
    return NULL;
}

// Removes the list node with reference 'reference' in the list.
element_t* spl_remove_at_reference(splist_t* list, splist_node_t* reference) {
    //TODO: implement remove method
    return NULL;
}