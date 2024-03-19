#include "splist.h"
#include <check.h>
#include <stdlib.h>
#include <stdio.h>

char letters[] = {'A', 'B', 'C', 'D'};

void setup(void) {
    // Implement pre-test setup
}

void teardown(void) {
    // Implement post-test teardown
}
START_TEST(test_ListFree)
    {
        // Test free NULL
        splist_t *list = NULL;
        spl_free(&list);
        ck_assert_msg(list == NULL, "Failure: expected result to be NULL");

        // Test free empty list
        list = spl_create();
        spl_free(&list);
        ck_assert_msg(list == NULL, "Failure: expected result to be NULL");
        
        // Test free with one element
        list = spl_create();
        list = spl_insert_at_reference(list, &letters[0], NULL);
        spl_free(&list);
        ck_assert_msg(list == NULL, "Failure: expected result to be NULL");

        // Test free with multiple elements
        list = spl_create();
        list = spl_insert_at_reference(list, &letters[0], NULL);
        list = spl_insert_at_reference(list, &letters[1], NULL);
        list = spl_insert_at_reference(list, &letters[2], NULL);
        spl_free(&list);
        ck_assert_msg(list == NULL, "Failure: expected result to be NULL");

    }
END_TEST

START_TEST(test_listInsertAtReference)
    {
        // Test inserting in NULL list
        splist_t *list = spl_insert_at_reference(NULL, &letters[0], NULL);
        ck_assert_msg(list == NULL, "Failure: expected list to be NULL");


        // Test inserting elements
        list = spl_create();
        //subtest lenght of list
        ck_assert_msg(spl_size(list) == -2, "Failure: expected list to have size of -2, got: %d", spl_size(list));
        
        //test inserting an element in an empty list (case 1, empty list)
        list = spl_insert_at_reference(list, &letters[2], NULL);
        ck_assert_msg(spl_size(list) == 1, "Failure: expected list to have size of 1, got a size of %d",
                      spl_size(list));

        //test inserting another element in list (case 2, reference == list->head)
        splist_node_t* reference = spl_get_first_reference(list);  
        list = spl_insert_at_reference(list, &letters[0], reference);
        ck_assert_msg(spl_size(list) == 2, "Failure: expected list to have size of 2, got a size of %d",
                      spl_size(list));

        //test inserting a third element (case 3, reference == NULL)
        list = spl_insert_at_reference(list, &letters[3], NULL);
        ck_assert_msg(spl_size(list) == 3, "Failure: expected list to have size of 3, got a size of %d",
                      spl_size(list));

        //test inserting a fourth element (case 4, reference != NULL)
        reference = spl_get_first_reference(list); 
        reference = spl_get_next_reference(list, reference);    //reference points to 2nd element in list reference points wrong
        list = spl_insert_at_reference(list, &letters[1], reference);
        ck_assert_msg(spl_size(list) == 4, "Failure: expected list to have size of 4, got a size of %d", spl_size(list));

        //test if the elements are in right order
        reference = spl_get_first_reference(list);
        char* data = spl_get_element_at_reference(list, reference);
        ck_assert_msg(*data == letters[0], "Failure: expected element to be %c, got: %c", letters[0], *data);

        reference = spl_get_next_reference(list, reference);
        data = spl_get_element_at_reference(list, reference);
        ck_assert_msg(*data == letters[1], "Failure: expected element to be %c, got: %c", letters[1], *data);
        
        reference = spl_get_next_reference(list, reference);
        data = spl_get_element_at_reference(list, reference);
        ck_assert_msg(*data == letters[2], "Failure: expected element to be %c, got: %c", letters[2], *data);
        
        reference = spl_get_next_reference(list, reference);
        data = spl_get_element_at_reference(list, reference);
        ck_assert_msg(*data == letters[3], "Failure: expected element to be %c, got: %c", letters[3], *data);
        
        //check if reference == last_reference
        ck_assert_msg(reference == spl_get_last_reference(list), "Failure: expected pointer to be the last element");
        
        //free the list
        spl_free(&list);
        ck_assert_msg(list == NULL, "Failure: expected list to be NULL");
    }
END_TEST


START_TEST(test_getReferences)
    {
        //list setup
        splist_t* list = spl_create();
        list = spl_insert_at_reference(list, &letters[0], NULL);
        list = spl_insert_at_reference(list, &letters[1], NULL);
        list = spl_insert_at_reference(list, &letters[2], NULL);

        splist_node_t* reference1 = spl_get_last_reference(list);
        int (*compare)(char* x, char* y) = compareChar;
        splist_node_t* reference2 = spl_get_reference_of_element(list, &letters[2], compare);

        ck_assert_msg(reference1 == reference2, "Failure: expected references to be the same");

        spl_free(&list);

    }
END_TEST

START_TEST(test_removeReferences)
    {
        //list setup
        splist_t* list = NULL;
        ck_assert_msg(spl_remove_at_reference(list, NULL) == NULL, "Failure: expected NULL for a list that has not been created");

        list = spl_create();
        ck_assert_msg(spl_remove_at_reference(list, NULL) == NULL, "Failure: expected NULL for a list with head == NULL");

        list = spl_insert_at_reference(list, &letters[0], NULL);
        list = spl_insert_at_reference(list, &letters[1], NULL);
        list = spl_insert_at_reference(list, &letters[2], NULL);
        list = spl_insert_at_reference(list, &letters[3], NULL);

        //remove the last element
        splist_node_t* lastRef = spl_get_last_reference(list);
        element_t* element = spl_remove_at_reference(list, lastRef);
        ck_assert_msg(*element == letters[3], "Failure: expected element to be D at removal, got: %c", *element);

        //check if references are good
        ck_assert_msg(lastRef != spl_get_last_reference(list), "Failure: expected references to not be the same");

        //remove an element in the middle of the list
        splist_node_t* reference = spl_get_first_reference(list);
        reference = spl_get_next_reference(list, reference);
        element = spl_remove_at_reference(list, reference);
        ck_assert_msg(*element == letters[1], "Failure: expected element to be B at removal, got: %c", *element);

        //check removal for wrong reference
        ck_assert_msg(spl_remove_at_reference(list, reference) == NULL, "Failure: expected to be NULL");
    
        spl_free(&list);
    }   
END_TEST

int main(void) {
    Suite *s1 = suite_create("LIST_EX1");
    TCase *tc1_1 = tcase_create("Core");
    SRunner *sr = srunner_create(s1);
    int nf;

    suite_add_tcase(s1, tc1_1);
    tcase_add_checked_fixture(tc1_1, setup, teardown);
    tcase_add_test(tc1_1, test_ListFree);
    tcase_add_test(tc1_1, test_listInsertAtReference);
    tcase_add_test(tc1_1, test_getReferences);
    tcase_add_test(tc1_1, test_removeReferences);
    // Add other tests here...

    srunner_run_all(sr, CK_VERBOSE);

    nf = srunner_ntests_failed(sr);
    srunner_free(sr);

    return nf == 0 ? EXIT_SUCCESS : EXIT_FAILURE;
}
