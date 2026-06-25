#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdbool.h>
#include <CUnit/Basic.h>
#include <become_daemon.h> 

void run_daemon_logic(int sleep_time) {
    
    if (sleep_time <= 0) {
        exit(EXIT_FAILURE);    
    }
    
    become_daemon(0);

    sleep(sleep_time);
    exit(EXIT_SUCCESS);
}

void test_daemon_logic(void) {
    pid_t p_child = fork();
    CU_ASSERT_FALSE(p_child < 0);

    if (p_child == 0) {
        run_daemon_logic(1); 
        exit(EXIT_FAILURE);  
    } else {
        int status; 
        waitpid(p_child, &status, 0);
        usleep(100000);

        CU_ASSERT_TRUE(WIFEXITED(status));
        CU_ASSERT_EQUAL(WEXITSTATUS(status), EXIT_SUCCESS);
    }
}
void test_daemon_invalid_argument(void) {
    pid_t pid = fork();
    CU_ASSERT_FALSE(pid < 0);

    if (pid == 0) {
        run_daemon_logic(-5); 
        exit(EXIT_SUCCESS);   
    } else {
        int status;
        waitpid(pid, &status, 0);
        
        CU_ASSERT_NOT_EQUAL(WEXITSTATUS(status), EXIT_SUCCESS);
    }
}

static int init_core_suite(void) { return 0; }
static int clean_core_suite(void) { return 0; }

static bool add_daemon_suite(void) {
    CU_pSuite suite = CU_add_suite("daemon_test", init_core_suite, clean_core_suite);
    if (!suite) return false;

    if ((CU_add_test(suite, "test_daemon_logic", test_daemon_logic) == NULL) ||
        (CU_add_test(suite, "test_daemon_invalid_argument", test_daemon_invalid_argument) == NULL)) {
        return false;
    }
    return true;
}

int main() {
    int failures = 0;
    if (CUE_SUCCESS != CU_initialize_registry()) {
        fprintf(stderr, "Failed to initialize registry: %s\n", CU_get_error_msg());
        return CU_get_error();
    }

    if (!add_daemon_suite()) {
        fprintf(stderr, "Failed to add string test suite: %s\n", CU_get_error_msg());
        CU_cleanup_registry();
        return CU_get_error();
    }

    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();
    
    failures = CU_get_number_of_failures();
    CU_cleanup_registry();
    return CU_get_error();
}
