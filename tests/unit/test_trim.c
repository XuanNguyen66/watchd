#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>
#include <CUnit/CUError.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <trim.h>

static int init_core_suite() {return 0;}
static int clean_core_suite() {return 0;}

// add suites test
void test_trim_function(void){
    char str1[] = "   hello world   ";
    trimline(str1);
    CU_ASSERT_STRING_EQUAL(str1, "hello world");
    
    char str2[] = "   hello";
    trimline(str2);
    CU_ASSERT_STRING_EQUAL(str2, "hello");

    char str3[] = "world   ";
    trimline(str3);
    CU_ASSERT_STRING_EQUAL(str3, "world");

    char str4[] = "/usr/bin";
    trimline(str4);
    CU_ASSERT_STRING_EQUAL(str4, "/usr/bin");

    char str5[] = "   ";
    trimline(str5);
    CU_ASSERT_STRING_EQUAL(str5, "");

}


static bool addStringSuite() {
    // create and registry suite in Registry
    CU_pSuite suite = CU_add_suite("string_utils", init_core_suite, clean_core_suite);
    if (!suite) {
        return false;
    }

    // registry test_case in Suite
    return (CU_ADD_TEST(suite, test_trim_function) != NULL);
}

int main(){
    // init regitry
    int failures = 0;
    if(CUE_SUCCESS != CU_initialize_registry()){
        fprintf(stderr, "Failed to initialize registry: %s\n", CU_get_error_msg());
        goto done;
    }

    // add suites -> add tests
    if (!addStringSuite()) {
        fprintf(stderr, "Failed to add string test suite: %s\n", CU_get_error_msg());
        goto cleanup;
    }
    
    // run test suites
    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();
    
    // cleanup
    failures = CU_get_number_of_failures();

cleanup:
    CU_cleanup_registry();

done:
    return failures ? EXIT_FAILURE : CU_get_error();
}
