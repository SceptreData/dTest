#include <stdio.h>
#include <stddef.h>
#include <setjmp.h>

static const char PASS_STRING[]         = "PASS";
static const char FAIL_STRING[]         = "FAIL";
static const char LINE_BREAK_STRING[]   = "--------------------";

#define TEST_ASSERT(condition, line_num, string)    \
            if(!condition) FailTest((line_num), (string))

#define RUN_TEST (func) RunTest(func, #func, __LINE__)

#define SET_EXIT_POINT() (setjmp(testResults.exit_point))

#define RETURN_TO_EXIT_POINT                  \
    do{                                       \
        testResults.active_test_failed = 1;   \
        longjmp(testResults.exit_point, 1);   \
    } while(0)

#define PRINT_EOL()     putchar('\n')

struct _test_results_t
{
    const char *active_file;
    const char *active_test;
    int cur_line;
    int num_tests;
    int num_success_tests;
    int num_failed_tests;
    int active_test_failed;
    jmp_buf exit_point;
};
extern struct _test_results_t testResults;

typedef void (*testFunction_t)(void);

void RunTest (testFunction_t Func, const char *func_name, const int func_line_num)
{
    testResults.active_test = func_name;
    testResults.cur_line_num = func_line_num;
    testResults.num_tests++;

    SET_EXIT_POINT();
    Func();

    EndActiveTest();
}

void EndActiveTest(void)
{
    if (testResults.active_test_failed){
        testResults.num_failed_tests++;
    } else {
        PrintTestInfo();
        printf("%s", PASS_STRING);
    }
    testResults.active_test_failed = 0;
    PRINT_EOL();
    fflush(stdout);
}

void FailTest(const char *str, int line_num)
{
    if (testResults.active_test_failed)
        return;

    PrintTestInfo(testResults.active_file, line_num);
    printf("%s", FAIL_STRING);

    if (str != NULL){
        printf(": %s", str)
    }
    RETURN_TO_EXIT_POINT;
}

void EndActiveTest();
void BeginTests (const char* filename)
{
    testResults.active_file = filename;
    testResults.active_test = NULL;
    testResults.cur_line_num = 0;
    testResults.num_tests = 0;
    testResults.num_success_tests = 0;
    testResults.num_failed_tests = 0;
    testResults.actve_test_failed = 0;
}

int EndTesting((void)
{
    PRINT_EOL();
    printf("%s\n", LINE_BREAK_STRING);
    printf("Tests: %d | Fails: %d\n", testResults.num_tests, testResults.num_failed_tests);
    if( testResults.num_failed_tests == 0 ){
        printf("Passed all tests.");
    } else {
        printf("FAIL");
    }
    PRINT_EOL();
    fflush(stdout);
    return testResults.num_failed_tests;
}


void PrintTestInfo(void)
{
    const char *file = testResults.active_file;
    int line_num = testResults.cur_line_num;
    const char *test_name;
    if (file != NULL){
        printf("%s: %d : %s : ", file, line_num, test_name);
    }
}
