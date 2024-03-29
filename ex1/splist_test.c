#include "splist.h"
#include <check.h>
#include <stdlib.h>
#include <stdio.h>

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
        // TODO : Test free with one element

        // TODO : Test free with multiple element

    }
END_TEST

START_TEST(test_ListInsertAtIndexListNULL)
    {
        // Test inserting at index -1
        char letter = 'A';
        splist_t *result = spl_insert_at_index(NULL, &letter, -1);
        ck_assert_msg(result == NULL, "Failure: expected list to be NULL");
        // TODO : Test inserting at index 0

        // TODO : Test inserting at index 99
    }
END_TEST

START_TEST(test_ListInsertAtIndexListEmpty)
{
    // Test inserting at index -1
    splist_t *list = spl_create();
    char letter = 'A';
    splist_t *result = spl_insert_at_index(list, &letter, -1);
    ck_assert_msg(spl_size(result) == 1, "Failure: expected list to have size of 1, got a size of %d",
                                         spl_size(result));
    spl_free(&list);
    // TODO : Test inserting at index 0

    // TODO : Test inserting at index 99
}
END_TEST

//START_TEST(test_nameOfYourTest)
//  Add other testcases here...
//END_TEST

int main(void) {
    Suite *s1 = suite_create("LIST_EX1");
    TCase *tc1_1 = tcase_create("Core");
    SRunner *sr = srunner_create(s1);
    int nf;

    suite_add_tcase(s1, tc1_1);
    tcase_add_checked_fixture(tc1_1, setup, teardown);
    tcase_add_test(tc1_1, test_ListFree);
    tcase_add_test(tc1_1, test_ListInsertAtIndexListNULL);
    tcase_add_test(tc1_1, test_ListInsertAtIndexListEmpty);
    // Add other tests here...

    srunner_run_all(sr, CK_VERBOSE);

    nf = srunner_ntests_failed(sr);
    srunner_free(sr);

    return nf == 0 ? EXIT_SUCCESS : EXIT_FAILURE;
}
