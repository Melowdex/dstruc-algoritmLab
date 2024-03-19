#ifndef _SPLIST_H
#define _SPLIST_H

typedef char element_t;

/** splist_t is a struct containing at least a head pointer to the start of the list; */
typedef struct splist splist_t;
/** splist_node_t is a struct containing relevant info for one node in the list; */
typedef struct splist_node splist_node_t;

/** Create and allocate memory for a new list.
 * \return a pointer to a newly-allocated and initialized list.
 */
splist_t* spl_create();

/** Deletes all elements in the list.
 * - Every list node of the list needs to be deleted. (free memory)
 * - The list itself also needs to be deleted. (free all memory)
 * - '*list' must be set to NULL.
 * \param list a double pointer to the list
 */
void spl_free(splist_t** list); 

/** Returns the number of elements in the list.
 * - If 'list' is NULL, -2 is returned.
 * \param list a pointer to the list
 * \return the size of the list
 */
int spl_size(splist_t* list);  

/** Inserts a new list node containing an 'element' in the list at position 'reference'.
 * - If 'list' is is NULL, NULL is returned.
 * - If 'reference' is NULL, the element is inserted at the end of the list.
 * - If 'reference' is not an existing reference in the list, 'list' is returned (nothing is inserted).
 * \param list a pointer to the list
 * \param element a pointer to an element
 * \param reference a pointer to a certain node in the list
 * \return a pointer to the list or NULL
 */
splist_t* spl_insert_at_reference(splist_t* list, element_t* element, splist_node_t* reference);   

/** Removes the list node with reference 'reference' in the list.
 * - The list node itself should always be freed.
 * - If 'reference' is NULL, NULL is returned (nothing is removed)
 * - If 'list' is is NULL, NULL is returned.
 * - If 'reference' is not an existing reference in the list, NULL is returned (nothing is removed).
 * \param list a pointer to the list
 * \param reference a pointer to a certain node in the list
 * \return a pointer to the element data of the node that is removed
 */
element_t* spl_remove_at_reference(splist_t* list, splist_node_t* reference);   

/** Returns the element contained in the list node with reference 'reference' in the list.
 * - If the list is empty, NULL is returned.
 * - If 'list' is NULL, NULL is returned.
 * - If 'reference' is NULL, NULL is returned.
 * - If 'reference' is not an existing reference in the list, NULL is returned.
 * \param list a pointer to the list
 * \param reference a pointer to a certain node in the list
 * \return the element contained in the list node or NULL
 */
element_t* spl_get_element_at_reference(splist_t* list, splist_node_t* reference);  

/** Returns a reference to the next list node of the list node with reference 'reference' in the list.
 * - If the list is empty, NULL is returned.
 * - If 'list' is is NULL, NULL is returned.
 * - If 'reference' is NULL, NULL is returned.
 * - If 'reference' is not an existing reference in the list, NULL is returned.
 * \param list a pointer to the list
 * \param reference a pointer to a certain node in the list
 * \return a pointer to the node next to 'reference' in the list or NULL
 */
splist_node_t* spl_get_next_reference(splist_t* list, splist_node_t* reference);    

/** Returns a reference to the first list node of the list.
 * - If the list is empty, NULL is returned.
 * - If 'list' is is NULL, NULL is returned.
 * \param list a pointer to the list
 * \return a reference to the first list node of the list or NULL
 */
splist_node_t* spl_get_first_reference(splist_t* list); 

/** Returns a reference to the last list node of the list.
 * - If the list is empty, NULL is returned.
 * - If 'list' is is NULL, NULL is returned.
 * \param list a pointer to the list
 * \return a reference to the last list node of the list or NULL
 */
splist_node_t* spl_get_last_reference(splist_t* list);  


/** COMPARE USING FUNCTION POINTERS
 *  ------------------------------- */

/** Returns a reference to the first list node in the list containing 'element'.
 * - If the list is empty, NULL is returned.
 * - If 'list' is is NULL, NULL is returned.
 * - If 'element' is not found in the list, NULL is returned.
 * \param list a pointer to the list
 * \param element a pointer to an element
 * \return the first list node in the list containing 'element' or NULL
 */
splist_node_t* spl_get_reference_of_element(splist_t* list, element_t* element, int (*compare)(element_t* x, element_t* y));

/** Sorts the elements in the list according to the given compare function.
 * - The sorting is done in ascending order.
 * - If two members compare as equal, their order in the sorted array is undefined.
 * - If 'list' is is NULL, NULL is returned.
 * \param list a pointer to the list
 * \param element the element to be inserted
 * \param compare pointer to compare function
 * \return a pointer to the list or NULL
 */
splist_t* spl_insert_sorted(splist_t* list, element_t* element,int (*compare)(element_t* x, element_t* y));

int compareChar(char* x, char* y);

#endif //_SPLIST_H