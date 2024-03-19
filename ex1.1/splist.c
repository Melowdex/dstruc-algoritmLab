#include <stdlib.h>
#include <string.h>
#include "splist.h"

typedef struct splist_node splist_node_t;
struct splist_node {
    splist_node_t* next;
    element_t* data;
};

struct splist {
    splist_node_t* head;
    int length;
};

int compareChar(char* x, char* y){
    return strcmp(x, y);
}

// Create and allocate memory for a new list.
splist_t* spl_create(){

    splist_t* new_list = malloc(sizeof(splist_t));
    new_list->head = NULL;
    new_list->length = 0; 

    return new_list;
}

void spl_free(splist_t** list){

    if (*list != NULL){

        splist_node_t* curr = (**list).head;
        splist_node_t* next;

        while (curr != NULL){
            next = curr->next;
            free(curr);
            curr = next;
        }

        free(*list);

        *list = NULL;
    }
}

// Returns the number of elements in the list.
int spl_size(splist_t* list){
    if (list->head == NULL)
        return -2;
    return list->length;
}

/*
 * pre: list exists with one element already in it   
 **/
static splist_node_t* find_reference(splist_t* list, splist_node_t* reference){
    splist_node_t* curr = list->head;
    while (curr->next != reference){
        curr = curr->next; 
        if (reference != NULL && curr->next == NULL)
            return NULL;
    }
    return curr;
}

/* Important note: to implement any list manipulation operator (insert, append, delete, sort, ...), always be aware of the following cases:
 * 1. empty list ==> avoid errors
 * 2. do operation at the start of the list ==> typically requires some special pointer manipulation
 * 3. do operation at the end of the list ==> typically requires some special pointer manipulation
 * 4. do operation in the middle of the list ==> default case with default pointer manipulation
 * ALWAYS check that you implementation works correctly in all these cases (check this on paper with list representation drawings!)
 **/
splist_t* spl_insert_at_reference(splist_t* list, element_t* element, splist_node_t* reference){

    if (list == NULL){
        return NULL;
    }
    
    splist_node_t* new_node = malloc(sizeof(splist_node_t));
    new_node->data = element;
    ++(list->length);

    if (list->head == NULL) { // covers case 1
        
        list->head = new_node;
        new_node->next = NULL;

    } else if (list->head == reference) {  // covers case 2
        
        list->head = new_node;
        new_node->next = reference;

    } else {  //covers case 3 and 4
        splist_node_t* prev_node = find_reference(list, reference);

        if (prev_node != NULL){
            new_node->next = reference;  
            prev_node->next = new_node;
        }
    }
    return list;
}

// Returns the element contained in the list node with reference 'reference' in the list.
element_t* spl_get_element_at_reference(splist_t* list, splist_node_t* reference) {

    if (list == NULL || list->head == NULL || reference == NULL)
        return NULL;
    
    splist_node_t* prev = find_reference(list, reference);  //to check if reference is in list
    if (prev == NULL && reference != list->head)
        return NULL;
    return reference->data;
}

// Removes the list node with reference 'reference' in the list.
element_t* spl_remove_at_reference(splist_t* list, splist_node_t* reference) {

    if (list == NULL || list->head == NULL || reference == NULL || find_reference(list, reference) == NULL)
        return NULL;

    element_t* data = NULL;

    if (reference == list->head){
        list->head = reference->next;

    } else {
        splist_node_t* prev = find_reference(list, reference);
        splist_node_t* next = reference->next;

        prev->next = next;
    } 

    data = reference->data;
    free(reference);

    return data;  
}

splist_node_t* spl_get_next_reference(splist_t* list, splist_node_t* reference){
    if (list == NULL || list->head == NULL || reference == NULL)
        return NULL;

    splist_node_t* prev = find_reference(list, reference);  //to make sure that reference is in list
    if (prev == NULL && reference != list->head)
        return NULL;
    return reference->next;
}

splist_node_t* spl_get_first_reference(splist_t* list){
    if (list == NULL)
        return NULL;

    return list->head;
}

splist_node_t* spl_get_last_reference(splist_t* list){
    if (list == NULL || list->head == NULL)
        return NULL;

    return find_reference(list, NULL); 
}

splist_node_t* spl_get_reference_of_element(splist_t* list, element_t* element, int (*compare)(element_t* x, element_t* y)){
    if (list == NULL || list->head == NULL)
        return NULL;
    
    splist_node_t* curr = list->head;
    int result;

    while (curr != NULL){
        result = compare(curr->data, element);
        if (result == 0)
            return curr;
        curr = curr->next;
    }
    return NULL;
}

splist_t* spl_insert_sorted(splist_t* list, element_t* element,int (*compare)(element_t* x, element_t* y)){
    if (list == NULL){
        return NULL;
    }

    splist_node_t* curr = list->head;
    int result;

    if (curr == NULL){
        return spl_insert_at_reference(list, element, NULL);
    }

    while (curr != NULL){
        result = compare(curr->data, element);
        if (result > 0)
            return spl_insert_at_reference(list, element, curr->next);
        else if(result < 0)
            curr = curr->next;
        else 
            return spl_insert_at_reference(list, element, curr);
    }

    return spl_insert_at_reference(list, element, NULL);
}