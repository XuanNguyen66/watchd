#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>
#include <CUnit/CUError.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "parseline.h"
#include "trim.h"


static int init_core_suite() {return 0;}
static int clean_core_suite() {return 0;}

void test_parse_key_value(void) {
    SecWatchManager manager;
    memset(&manager, 0, sizeof(SecWatchManager));

    char line1[] = "[service]";
    parseline(line1, &manager);
    CU_ASSERT_EQUAL(manager.total_services, 1);

    char line2[] = "name=sleep_service";
    parseline(line2, &manager);
    
    printf("\n[DEBUG NAME] Actual name saved is: '%s'\n", manager.services[0].name);
    CU_ASSERT_STRING_EQUAL(manager.services[0].name, "sleep_service");

    char line3[] = "cmd=/usr/bin/sleep 10";
    parseline(line3, &manager);

    printf("[DEBUG CMD] Actual cmd after strtok is: '%s'\n", manager.services[0].cmd);
    
    CU_ASSERT_STRING_EQUAL(manager.services[0].cmd, "/usr/bin/sleep");
    CU_ASSERT_STRING_EQUAL(manager.services[0].argv[0], "/usr/bin/sleep");
    CU_ASSERT_STRING_EQUAL(manager.services[0].argv[1], "10");
}

static bool addStringSuite() {
    // create and registry suite in Registry
    CU_pSuite suite = CU_add_suite("paser_utils", init_core_suite, clean_core_suite);
    if (!suite) {
        return false;
    }

    // registry test_case in Suite
    return (CU_ADD_TEST(suite, test_parse_key_value) != NULL);
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
