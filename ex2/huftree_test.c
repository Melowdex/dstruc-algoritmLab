#include "huftree.h"
#include "splist.h"
#include <check.h>
#include <stdlib.h>
#include <stdio.h>

freq_data_t freq_data[] = {
        { .letter = 'r', .frequency = 4 },
        { .letter = 't', .frequency = 5 },
        { .letter = 'u', .frequency = 10 },
        { .letter = 'a', .frequency = 15 },
        { .letter = 'd', .frequency = 18 },
        { .letter = 'e', .frequency = 29 }
};

START_TEST(test_HufCreate)
    {
        // Test create NULL
        huftree_t* huftree = NULL;
        huftree = huf_create(NULL, 0);
        ck_assert_msg(huftree != NULL, "Failure: expected result to be not NULL");
        huf_free(&huftree);
        ck_assert_msg(huftree == NULL, "Failure: expected result to be NULL");

        // test create with one element
        huftree = huf_create(freq_data, 1);
        ck_assert_msg(huftree != NULL, "Failure: expected result to be not NULL");
        huf_free(&huftree);
        ck_assert_msg(huftree == NULL, "Failure: expected result to be NULL");

        // test create with multiple elements
        huftree = huf_create(freq_data, 6);
        ck_assert_msg(huftree != NULL, "Failure: expected result to be not NULL");
        huf_free(&huftree);
        ck_assert_msg(huftree == NULL, "Failure: expected result to be NULL");
    }
END_TEST

START_TEST(test_HufEncode)
{
    // test create with multiple elements
    huftree_t* huftree = huf_create(freq_data, 6);
    ck_assert_msg(huftree != NULL, "Failure: expected result to be not NULL");
    uint8_t out[10];
    
    int amount = huf_encode(huftree,"r",out);
    ck_assert_int_eq(amount,4);
    ck_assert_int_eq(out[0] & 0b00001111, 0b00001110);

    amount = huf_encode(huftree,"ra",out);
    ck_assert_int_eq(amount,6);
    ck_assert_int_eq(out[0] & 0b00111111, 0b00111110);

    amount = huf_encode(huftree,"dau",out);
    ck_assert_int_eq(amount,7);
    ck_assert_int_eq(out[0] & 0b01111111, 0b00101101);

    huf_free(&huftree);
}
END_TEST

START_TEST(test_HufDecode)
{
    // test create with multiple elements
    huftree_t* huftree = huf_create(freq_data, 6);
    ck_assert_msg(huftree != NULL, "Failure: expected result to be not NULL");
    uint8_t out[10];

    out[0] =  0b00001110;
    char* result = huf_decode(huftree, out,4);
    ck_assert_str_eq(result,"r");
    free(result);

    out[0] =  0b00111110;
    result = huf_decode(huftree, out,6);
    ck_assert_str_eq(result,"ra");
    free(result);

    out[0] =  0b00101101;
    result = huf_decode(huftree, out,7);
    ck_assert_str_eq(result,"dau");
    free(result);

    huf_free(&huftree);
}
END_TEST

//START_TEST(test_nameOfYourTest)
//  Add other testcases here...
//END_TEST

int main(void) {
    Suite *s1 = suite_create("HUFTREE_EX2");
    TCase *tc1_1 = tcase_create("Core");
    SRunner *sr = srunner_create(s1);
    int nf;

    suite_add_tcase(s1, tc1_1);
    tcase_add_checked_fixture(tc1_1, NULL, NULL);
    tcase_add_test(tc1_1, test_HufCreate);
    tcase_add_test(tc1_1, test_HufEncode);
    tcase_add_test(tc1_1, test_HufDecode);
    // Add other tests here...

    srunner_run_all(sr, CK_VERBOSE);

    nf = srunner_ntests_failed(sr);
    srunner_free(sr);

    return nf == 0 ? EXIT_SUCCESS : EXIT_FAILURE;
}
